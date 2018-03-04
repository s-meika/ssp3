/*
 *  TOPPERS/SSP単体テストヘッダファイル
 */

#ifndef SSP_TEST_H
#define SSP_TEST_H

#ifndef TOPPERS_MACRO_ONLY

extern void task1(intptr_t exinf);
extern void task2(intptr_t exinf);
extern void task3(intptr_t exinf);
extern void task4(intptr_t exinf);

extern void int_handler_0(void);
extern void int_handler_4(void);

extern void exc_handler_0(void *excinf);
extern void exc_handler_1(void *excinf);

#endif /* TOPPERS_MACRO_ONLY */

#endif /* SSP_TEST_H */
