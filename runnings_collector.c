#include <uwsgi.h>
#include <stdlib.h>

extern struct uwsgi_server uwsgi;


/**
 * Collects and logs overlimitet running requests.
 */
int64_t runnings_collector(struct uwsgi_metric * metric) {
    if (!metric->arg2) {
        uwsgi_log("metric \"%s\" requires integer arg2 argument\n", metric->name);
        return 0;
    }

    int64_t limit = strtol(metric->arg2, NULL, 10);
    if (limit <= 0) {
        uwsgi_log("metric \"%s\" requires positive arg2 argument\n", metric->name);
        return 0;
    }

    int64_t now = uwsgi_now();
    int64_t overlimited = 0;

    for (int wid = 0; wid < uwsgi.numproc + 1; wid++) {
        for (int cid = 0; cid < uwsgi.cores; cid++) {
            if (uwsgi.workers[wid].cores[cid].in_request) {
                if (now - uwsgi.workers[wid].cores[cid].req.start_of_request_in_sec >= limit) {
                    overlimited++;
                }
            }
        }
    }

    return overlimited;
}
