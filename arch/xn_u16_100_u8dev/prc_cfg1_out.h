/*
 *		cfg1_out.cのリンクに必要なスタブの定義
 */

void sta_ker(void)
{
}

void hardware_init_hook(void)
{
}

void software_init_hook(void)
{
}

ER syslog_wri_log(uint_t prio, const SYSLOG *p_syslog)
{
	return E_OK;
}

bool_t _kernel_make_runnable(TCB *p_tcb)
{
	return false;
}

bool_t _kernel_make_non_runnable(TCB *p_tcb)
{
	return false;
}

void _kernel_tmevtb_insert(TMEVTB *p_tmevtb, EVTTIM time)
{
}

void _kernel_tmevtb_delete(TMEVTB *p_tmevtb)
{
}

const SIZE		_kernel_istksz = 0;

STK_T *const	_kernel_istk = NULL;

volatile bool_t		_kernel_lock_flag = false;
volatile uint16_t	_kernel_saved_iipm = 0;
volatile int		_kernel_int_cnt = 0;

EVTTIM _kernel_next_time = 0;

TCB	*_kernel_p_runtsk = NULL;
TCB _kernel_tcb_table[1];

/*
 *  オフセットファイルを生成するための定義
 */
const uint8_t	MAGIC_1 = 0x12;
const uint16_t	MAGIC_2 = 0x1234;
const uint32_t	MAGIC_4 = 0x12345678;

const TCB	TCB_enatex = {
	{ NULL, NULL },			/* task_queue */
	NULL,					/* p_tinib */
	0U,						/* tstat */
#ifdef TOPPERS_SUPPORT_MUTEX
	0U,						/* bpriority */
#endif /* TOPPERS_SUPPORT_MUTEX */
	0U,						/* priority */
	false,					/* acqeue */
	false,					/* wupque */
	true,					/* enatex */
	0U,						/* texptn */
	NULL,					/* p_winifo */
#ifdef TOPPERS_SUPPORT_MUTEX
	{ NULL, NULL },			/* mutex_queue */
#endif /* TOPPERS_SUPPORT_MUTEX */
#ifdef TOPPERS_SUPPORT_OVRHDR
	0U,						/* leftotm */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	{ NULL, NULL }			/* tskctxb */
};
