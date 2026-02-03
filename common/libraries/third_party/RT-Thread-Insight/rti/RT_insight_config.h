#ifndef __RT_INSIGHT_CONFIG_H__
#define __RT_INSIGHT_CONFIG_H__

/* ---------------- Insight Track Type Masks ---------------- */
#define BASE_MASK (0xF0000000UL) /**< Base mask for track type category */
#define FUNC_MASK (0x000000FFUL) /**< Mask for specific function/track type */

/* ---------------- Thread Track Type ---------------- */
#define THREAD_TRACK_BASE (0x00000000UL)                 /**< Base track type for threads */
#define THREAD_RUN        (THREAD_TRACK_BASE + (1 << 1)) /**< Thread running */
#define THREAD_EXIT       (THREAD_TRACK_BASE + (1 << 2)) /**< Thread exit */
#define THREAD_RESUME     (THREAD_TRACK_BASE + (1 << 3)) /**< Thread resumed */
#define THREAD_SUSPEND    (THREAD_TRACK_BASE + (1 << 4)) /**< Thread suspended */

/* ---------------- IRQ / ISR Track Type ---------------- */
#define IRQ_TRACK_BASE (0x10000000UL)              /**< Base track type for IRQs */
#define IRQ_ENTER      (IRQ_TRACK_BASE + (1 << 1)) /**< IRQ enter */
#define IRQ_EXIT       (IRQ_TRACK_BASE + (1 << 2)) /**< IRQ exit */

/* ---------------- Timer Track Type ---------------- */
#define TIMER_TRACK_BASE (0x20000000UL)                /**< Base track type for timers */
#define TIMER_ENTER      (TIMER_TRACK_BASE + (1 << 1)) /**< Timer callback start */
#define TIMER_EXIT       (TIMER_TRACK_BASE + (1 << 2)) /**< Timer callback end */

/* ---------------- Semaphore Track Type ---------------- */
#define SEM_TRACK_BASE (0x30000000UL)              /**< Base track type for semaphores */
#define SEM_TRYTAKE    (SEM_TRACK_BASE + (1 << 1)) /**< Attempt to take semaphore */
#define SEM_TAKE       (SEM_TRACK_BASE + (1 << 2)) /**< Semaphore taken */
#define SEM_RELEASE    (SEM_TRACK_BASE + (1 << 3)) /**< Semaphore released */

/* ---------------- Mutex Track Type ---------------- */
#define MUTEX_TRACK_BASE (0x40000000UL)                /**< Base track type for mutexes */
#define MUTEX_TRYTAKE    (MUTEX_TRACK_BASE + (1 << 1)) /**< Attempt to take mutex */
#define MUTEX_TAKE       (MUTEX_TRACK_BASE + (1 << 2)) /**< Mutex taken */
#define MUTEX_RELEASE    (MUTEX_TRACK_BASE + (1 << 3)) /**< Mutex released */

/* ---------------- Event Object Track Type ---------------- */
#define EVENT_TRACK_BASE (0x50000000UL)                /**< Base track type for event objects */
#define EVENT_TRYTAKE    (EVENT_TRACK_BASE + (1 << 1)) /**< Attempt to take event */
#define EVENT_TAKE       (EVENT_TRACK_BASE + (1 << 2)) /**< Event taken */
#define EVENT_RELEASE    (EVENT_TRACK_BASE + (1 << 3)) /**< Event released */

/* ---------------- Mailbox Track Type ---------------- */
#define MAILBOX_TRACK_BASE (0x60000000UL)                  /**< Base track type for mailboxes */
#define MAILBOX_TRYTAKE    (MAILBOX_TRACK_BASE + (1 << 1)) /**< Attempt to take mailbox */
#define MAILBOX_TAKE       (MAILBOX_TRACK_BASE + (1 << 2)) /**< Mailbox taken */
#define MAILBOX_RELEASE    (MAILBOX_TRACK_BASE + (1 << 3)) /**< Mailbox released */

/* ---------------- Message Queue Track Type ---------------- */
#define QUEUE_TRACK_BASE (0x70000000UL)                /**< Base track type for message queues */
#define QUEUE_TRYTAKE    (QUEUE_TRACK_BASE + (1 << 1)) /**< Attempt to take queue */
#define QUEUE_TAKE       (QUEUE_TRACK_BASE + (1 << 2)) /**< Queue taken */
#define QUEUE_RELEASE    (QUEUE_TRACK_BASE + (1 << 3)) /**< Queue released */

#endif // __RT_INSIGHT_CONFIG_H__
