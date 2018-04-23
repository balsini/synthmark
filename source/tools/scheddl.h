#if !defined(SYNTHMARK_SCHEDDL_H) && !defined(__APPLE__)
#define SYNTHMARK_SCHEDDL_H

#include <linux/sched.h>
#include <sys/syscall.h>
#include <unistd.h>


const __u64 SCHED_GETATTR_FLAGS_DL_ABSOLUTE = 0x01;

struct sched_attr {
    __u32 size;

    __u32 sched_policy;

    // For future implementation. By default should be set to 0.
    __u64 sched_flags;

    // SCHED_OTHER niceness
    __s32 sched_nice;

    // SCHED_RT priority
    __u32 sched_priority;

    // SCHED_DEADLINE parameters, in nsec
    __u64 sched_runtime;
    __u64 sched_deadline;
    __u64 sched_period;
};

inline int sched_setattr(pid_t pid,
                         const struct sched_attr *attr,
                         unsigned int flags) {
    return syscall(SYS_sched_setattr, pid, attr, flags);
}

inline int sched_getattr(pid_t pid,
                         struct sched_attr *attr,
                         unsigned int size,
                         unsigned int flags) {
    return syscall(SYS_sched_getattr, pid, attr, size, flags);
}

#endif /* SYNTHMARK_SCHEDDL_H */

