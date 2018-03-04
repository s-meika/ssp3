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
	CU_ASSERT_EQUAL(TNUM_TSKID, 2);
	
	CU_ASSERT_EQUAL(TASK_ID1,  2);
	CU_ASSERT_EQUAL(TASK_ID2,  1);
	
	CU_ASSERT_EQUAL(tmax_tskid,  2);
	
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[0], TA_ACT);
	CU_ASSERT_EQUAL(_kernel_tinib_tskatr[1], TA_ACT);
	
	CU_ASSERT_EQUAL(tinib_exinf[0], EXINF2);
	CU_ASSERT_EQUAL(tinib_exinf[1], EXINF1);
	
	CU_ASSERT_EQUAL(tinib_task[0], task2);
	CU_ASSERT_EQUAL(tinib_task[1], task1);
	
	CU_ASSERT_EQUAL(tinib_epriority[0], INT_PRIORITY(1));
	CU_ASSERT_EQUAL(tinib_epriority[1], INT_PRIORITY(2));
	
	CU_ASSERT_EQUAL(init_rdypmap, 0x03);
}

void task1(intptr_t exinf) {}
void task2(intptr_t exinf) {}
