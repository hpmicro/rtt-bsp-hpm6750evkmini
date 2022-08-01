/*
/*
 * Copyright (c) 2021-2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef APPLICATIONS_MSC_APP_H_
#define APPLICATIONS_MSC_APP_H_

#define FS_THREAD_MBOX_MSG_COUNT (10U)
#define FS_MSG_ID_MOUNT          (1U)
#define FS_MSG_ID_UNMOUNT        (2U)

typedef struct {
    uint8_t id;
    uint8_t dev_addr;
} msc_app_msg_t;

extern struct rt_mailbox tfs_thread_mb;
extern rt_ubase_t tfs_thread_mb_pool[];

#endif /* APPLICATIONS_MSC_APP_H_ */
