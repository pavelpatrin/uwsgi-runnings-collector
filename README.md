# Collects overlimited uwsgi request

This extension allows to log via uwsgi metrics how many current active (not finished) requests exceeded some limit in seconds.

This is useful for early problems detection: something happens and requests hang in background.

## Building extension

1. Build uwsgi from sources or download uwsgi includes

2. Compile collector shared library

```yaml
gcc `./uwsgi --cflags` -std=c99 -shared -fPIC -o runnings_collector.so runnings_collector.c
```

## Configuring uwsgi

1. Append .so preload option to uwsgi config

```yaml
dlopen: /home/vagrant/uwsgi/runnings_collector.so
```

2. Configure new metrics in uwsgi config

```yaml
metric: name=running.over_60s,collector=func,arg1=runnings_collector,arg2=60,freq=60
metric: name=running.over_120s,collector=func,arg1=runnings_collector,arg2=120,freq=60
metric: name=running.over_240s,collector=func,arg1=runnings_collector,arg2=240,freq=60
metric: name=running.over_480s,collector=func,arg1=runnings_collector,arg2=480,freq=60
metric: name=running.over_960s,collector=func,arg1=runnings_collector,arg2=960,freq=60
metric: name=running.over_1920s,collector=func,arg1=runnings_collector,arg2=1920,freq=60
metric: name=running.over_3840s,collector=func,arg1=runnings_collector,arg2=3840,freq=60
```