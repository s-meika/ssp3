#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <task.h>

extern const intptr_t   tinib_exinf[];                  /* タスクの拡張情報 */
extern const ATR        _kernel_tinib_tskatr[];
extern const TASK       tinib_task[];                   /* タスクの起動番地 */
extern const uint_t     tinib_epriority[];              /* タスクの実行時優先度（内部表現） */
extern const uint_t     init_rdypmap;

void
test_main(void)
{
	// タスクの定義
	CU_ASSERT_EQUAL(TNUM_TSKID, 16);
	
	CU_ASSERT_EQUAL(TASK_ID1,  3);
	CU_ASSERT_EQUAL(TASK_ID2,  2);
	CU_ASSERT_EQUAL(TASK_ID3,  5);
	CU_ASSERT_EQUAL(TASK_ID4,  7);
	CU_ASSERT_EQUAL(TASK_ID5,  8);
	CU_ASSERT_EQUAL(TASK_ID6,  4);
	CU_ASSERT_EQUAL(TASK_ID7,  1);
	CU_ASSERT_EQUAL(TASK_ID8,  6);
	CU_ASSERT_EQUAL(TASK_ID9,  11);
	CU_ASSERT_EQUAL(TASK_ID10,  10);
	CU_ASSERT_EQUAL(TASK_ID11,  13);
	CU_ASSERT_EQUAL(TASK_ID12,  15);
	CU_ASSERT_EQUAL(TASK_ID13,  16);
	CU_ASSERT_EQUAL(TASK_ID14,  12);
	CU_ASSERT_EQUAL(TASK_ID15,  9);
	CU_ASSERT_EQUAL(TASK_ID16,  14);
	
	CU_ASSERT_EQUAL(tmax_tskid,  16);
	
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[0], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[1], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[2], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[3], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[4], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[5], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[6], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[7], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[8], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[9], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[10], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[11], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[12], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[13], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[14], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[15], TA_ACT);
	
	CU_ASSERT_EQUAL(tinib_exinf[0], EXINF7);
	CU_ASSERT_EQUAL(tinib_exinf[1], EXINF2);
	CU_ASSERT_EQUAL(tinib_exinf[2], EXINF1);
	CU_ASSERT_EQUAL(tinib_exinf[3], EXINF6);
	CU_ASSERT_EQUAL(tinib_exinf[4], EXINF3);
	CU_ASSERT_EQUAL(tinib_exinf[5], EXINF8);
	CU_ASSERT_EQUAL(tinib_exinf[6], EXINF4);
	CU_ASSERT_EQUAL(tinib_exinf[7], EXINF5);
	
	CU_ASSERT_EQUAL(tinib_exinf[8], EXINF15);
	CU_ASSERT_EQUAL(tinib_exinf[9], EXINF10);
	CU_ASSERT_EQUAL(tinib_exinf[10], EXINF9);
	CU_ASSERT_EQUAL(tinib_exinf[11], EXINF14);
	CU_ASSERT_EQUAL(tinib_exinf[12], EXINF11);
	CU_ASSERT_EQUAL(tinib_exinf[13], EXINF16);
	CU_ASSERT_EQUAL(tinib_exinf[14], EXINF12);
	CU_ASSERT_EQUAL(tinib_exinf[15], EXINF13);
	
	CU_ASSERT_EQUAL(tinib_task[0], task7);
	CU_ASSERT_EQUAL(tinib_task[1], task2);
	CU_ASSERT_EQUAL(tinib_task[2], task1);
	CU_ASSERT_EQUAL(tinib_task[3], task6);
	CU_ASSERT_EQUAL(tinib_task[4], task3);
	CU_ASSERT_EQUAL(tinib_task[5], task8);
	CU_ASSERT_EQUAL(tinib_task[6], task4);
	CU_ASSERT_EQUAL(tinib_task[7], task5);
	CU_ASSERT_EQUAL(tinib_task[8], task15);
	CU_ASSERT_EQUAL(tinib_task[9], task10);
	CU_ASSERT_EQUAL(tinib_task[10], task9);
	CU_ASSERT_EQUAL(tinib_task[11], task14);
	CU_ASSERT_EQUAL(tinib_task[12], task11);
	CU_ASSERT_EQUAL(tinib_task[13], task16);
	CU_ASSERT_EQUAL(tinib_task[14], task12);
	CU_ASSERT_EQUAL(tinib_task[15], task13);
	
	CU_ASSERT_EQUAL(tinib_epriority[0], INT_PRIORITY(1));
	CU_ASSERT_EQUAL(tinib_epriority[1], INT_PRIORITY(2));
	CU_ASSERT_EQUAL(tinib_epriority[2], INT_PRIORITY(3));
	CU_ASSERT_EQUAL(tinib_epriority[3], INT_PRIORITY(4));
	CU_ASSERT_EQUAL(tinib_epriority[4], INT_PRIORITY(5));
	CU_ASSERT_EQUAL(tinib_epriority[5], INT_PRIORITY(6));
	CU_ASSERT_EQUAL(tinib_epriority[6], INT_PRIORITY(7));
	CU_ASSERT_EQUAL(tinib_epriority[7], INT_PRIORITY(8));
	CU_ASSERT_EQUAL(tinib_epriority[8], INT_PRIORITY(9));
	CU_ASSERT_EQUAL(tinib_epriority[9], INT_PRIORITY(10));
	CU_ASSERT_EQUAL(tinib_epriority[10], INT_PRIORITY(11));
	CU_ASSERT_EQUAL(tinib_epriority[11], INT_PRIORITY(12));
	CU_ASSERT_EQUAL(tinib_epriority[12], INT_PRIORITY(13));
	CU_ASSERT_EQUAL(tinib_epriority[13], INT_PRIORITY(14));
	CU_ASSERT_EQUAL(tinib_epriority[14], INT_PRIORITY(15));
	CU_ASSERT_EQUAL(tinib_epriority[15], INT_PRIORITY(16));
	
	CU_ASSERT_EQUAL(init_rdypmap, 0xffff);
}

void task1(intptr_t exinf) {}
void task2(intptr_t exinf) {}
void task3(intptr_t exinf) {}
void task4(intptr_t exinf) {}
void task5(intptr_t exinf) {}
void task6(intptr_t exinf) {}
void task7(intptr_t exinf) {}
void task8(intptr_t exinf) {}
void task9(intptr_t exinf) {}
void task10(intptr_t exinf) {}
void task11(intptr_t exinf) {}
void task12(intptr_t exinf) {}
void task13(intptr_t exinf) {}
void task14(intptr_t exinf) {}
void task15(intptr_t exinf) {}
void task16(intptr_t exinf) {}
