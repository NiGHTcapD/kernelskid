# kernelskid
kernel scheduler

This program is an example of an operating system's kernel, in how it schedules processes and resources.

There are resources 1 through 10, inclusive and preexisting, as well as an OS process of ID 0 and priority 0. 
Input commands with the title first, then one or two numbers as prompted.
cr/create/Cr/Create, then a number that serves as an ID, then another number that defines the priority of that process/thread. Priorities go from 0 (lowest) to 4 (highest) and the highest-priority process without a resource will be running.
rq/req/request/quest, then a number that defines the resource. The running program takes the resource and cedes 'running' to the highest priority process with no resource.
rl/rel/release/lease, then a number of a resource already used with the request command, undoes that command, releasing the resource from whatever process held it. If it had a higher priority than the running program, it takes over.
ds/des/destroy/troy, then a number ID of an existing process, kills the process and releases its resources. Running may change.
quit ends kernelskid.
