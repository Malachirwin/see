#include "system/stacktrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "line_stream.h"
#include "lt.h"
#include "lt/lt_adapters.h"
#include "system/nth_alloc.h"
#include "system/log.h"

struct LineStream
{
    Lt *lt;
    FILE *stream;
    char *buffer;
    size_t capacity;
};

static void fclose_lt(void* file)
{
    fclose(file);
}

LineStream *create_line_stream(const char *filename,
                               const char *mode,
                               size_t capacity)
{
    trace_assert(filename);
    trace_assert(mode);

    Lt *lt = create_lt();
    if (lt == NULL) {
        return NULL;
    }

    LineStream *line_stream = PUSH_LT(
        lt,
        nth_alloc(sizeof(LineStream)),
        free);
    if (line_stream == NULL) {
        RETURN_LT(lt, NULL);
    }
    line_stream->lt = lt;

    line_stream->stream = PUSH_LT(
        lt,
        fopen(filename, mode),
        fclose_lt);
    if (line_stream->stream == NULL) {
        log_fail("Could not open file '%s': %s\n", filename, strerror(errno));
        RETURN_LT(lt, NULL);
    }

    line_stream->buffer = PUSH_LT(
        lt,
        nth_alloc(sizeof(char) * capacity),
        free);
    if (line_stream->buffer == NULL) {
        RETURN_LT(lt, NULL);
    }

    line_stream->capacity = capacity;

    return line_stream;
}

void destroy_line_stream(LineStream *line_stream)
{
    trace_assert(line_stream);

    RETURN_LT0(line_stream->lt);
}

const char *line_stream_next(LineStream *line_stream)
{
    trace_assert(line_stream);
    return fgets(line_stream->buffer,
                 (int) line_stream->capacity,
                 line_stream->stream);
}
