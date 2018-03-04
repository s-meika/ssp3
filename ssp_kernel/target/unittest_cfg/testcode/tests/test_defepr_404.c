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
	CU_ASSERT_EQUAL(TNUM_TSKID, 4);
	
	CU_ASSERT_EQUAL(TASK_ID1,  1);
	CU_ASSERT_EQUAL(TASK_ID2,  4);
	CU_ASSERT_EQUAL(TASK_ID3,  3);
	CU_ASSERT_EQUAL(TASK_ID4,  2);
	
	CU_ASSERT_EQUAL(tmax_tskid,  4);
	
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[0], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[1], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[2], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[3], TA_ACT);
	
	CU_ASSERT_EQUAL(tinib_exinf[0], EXINF1);
	CU_ASSERT_EQUAL(tinib_exinf[1], EXINF4);
	CU_ASSERT_EQUAL(tinib_exinf[2], EXINF3);
	CU_ASSERT_EQUAL(tinib_exinf[3], EXINF2);
	
	CU_ASSERT_EQUAL(tinib_task[0], task1);
	CU_ASSERT_EQUAL(tinib_task[1], task4);
	CU_ASSERT_EQUAL(tinib_task[2], task3);
	CU_ASSERT_EQUAL(tinib_task[3], task2);
	
	CU_ASSERT_EQUAL(tinib_epriority[0], INT_PRIORITY(1));
	CU_ASSERT_EQUAL(tinib_epriority[1], INT_PRIORITY(2));
	CU_ASSERT_EQUAL(tinib_epriority[2], INT_PRIORITY(3));
	CU_ASSERT_EQUAL(tinib_epriority[3], INT_PRIORITY(2));
	
	CU_ASSERT_EQUAL(init_rdypmap, 0x0f);
}

void task1(intptr_t exinf) {}
void task2(intptr_t exinf) {}
void task3(intptr_t exinf) {}
void task4(intptr_t exinf) {}
