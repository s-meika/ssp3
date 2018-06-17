/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2017 by Meika Sugimoto
 * 
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *  �V���A��I/O�f�o�C�X�iSIO�j�h���C�o(RL78/G13�p)
 */

#include "kernel_impl.h"
#include "target_serial.h"
#include "chip_serial.h"
#include <sil.h>


#define INDEX_PORT(x)	((x) - 1)
#define GET_SIOPCB(x)	(&siopcb_table[INDEX_PORT(x)])

#define PER0_ADDR			((uint8_t __far *)0xF00F0)	/* ���ӃC�l�[�u���E���W�X�^ 0 */
#define NFEN0_ADDR			((uint16_t __far *)0xF0070)	/* �m�C�Y�E�t�B���^�����W�X�^ 0 */

/*
 *  UART��SAU�̃��j�b�g�C�`���l���̊֌W�͈ȉ��̒ʂ�
 *
 *  UART0 : SAU0 , ���M:�`���l��0 , ��M:�`���l��1
 *  UART1 : SAU0 , ���M:�`���l��2 , ��M:�`���l��3
 *  UART2 : SAU1 , ���M:�`���l��0 , ��M:�`���l��1
 *  UART3 : SAU1 , ���M:�`���l��2 , ��M:�`���l��3
 */
/*
 *  UART�`���l�����̃��W�X�^�A�h���X��`
 *
 *  SAU�̃��W�X�^��SFR�̈��ɓ_�݂��Ă���C�P���ȉ��Z��
 *  ���W�X�^�A�h���X���Z�o�ł��Ȃ����Ƃ���C�e�[�u������ǂݏo���������̗p����
 */
const SAU_REGADDRS sau_register_address_table[TNUM_UART_CH] =
{
	/* ID : 1 */
	{
		(__far uint16_t *)0xF0110 ,		/* SMR_tx */
		(__far uint16_t *)0xF0112 ,		/* SMR_rx */
		(__far uint16_t *)0xF0118 ,		/* SCR_tx */
		(__far uint16_t *)0xF011A ,		/* SCR_rx */
		(__far uint16_t *)0xFFF10 ,		/* SDR_tx */
		(__far uint16_t *)0xFFF12 ,		/* SDR_rx */
		(__far uint16_t *)0xF0108 ,		/* SIR */
		(__far uint16_t *)0xF0100 ,		/* SSR_tx */
		(__far uint16_t *)0xF0102 ,		/* SSR_rx */
		(__far uint8_t  *)0xF0126 ,		/* SPS */
		(__far uint16_t *)0xF0122 ,		/* SS  */
		(__far uint16_t *)0xF0124 ,		/* ST  */
		(__far uint16_t *)0xF012A ,		/* SOE */
		(__far uint16_t *)0xF0128  		/* SO */
	} ,
	/* ID : 2 */
	{
		(__far uint16_t *)0xF0114 ,		/* SMR_tx */
		(__far uint16_t *)0xF0116 ,		/* SMR_rx */
		(__far uint16_t *)0xF011C ,		/* SCR_tx */
		(__far uint16_t *)0xF011E ,		/* SCR_rx */
		(__far uint16_t *)0xFFF44 ,		/* SDR_tx */
		(__far uint16_t *)0xFFF46 ,		/* SDR_rx */
		(__far uint16_t *)0xF010C ,		/* SIR */
		(__far uint16_t *)0xF0104 ,		/* SSR_tx */
		(__far uint16_t *)0xF0106 ,		/* SSR_rx */
		(__far uint8_t  *)0xF0126 ,		/* SPS */
		(__far uint16_t *)0xF0122 ,		/* SS  */
		(__far uint16_t *)0xF0124 ,		/* ST  */
		(__far uint16_t *)0xF012A ,		/* SOE */
		(__far uint16_t *)0xF0128  		/* SO */
	} ,
	/* ID : 3 */
	{
		(__far uint16_t *)0xF0150 ,		/* SMR_tx */
		(__far uint16_t *)0xF0152 ,		/* SMR_rx */
		(__far uint16_t *)0xF0158 ,		/* SCR_tx */
		(__far uint16_t *)0xF015A ,		/* SCR_rx */
		(__far uint16_t *)0xFFF48 ,		/* SDR_tx */
		(__far uint16_t *)0xFFF4A ,		/* SDR_rx */
		(__far uint16_t *)0xF0148 ,		/* SIR */
		(__far uint16_t *)0xF0140 ,		/* SSR_tx */
		(__far uint16_t *)0xF0142 ,		/* SSR_rx */
		(__far uint8_t  *)0xF0166 ,		/* SPS */
		(__far uint16_t *)0xF0162 ,		/* SS  */
		(__far uint16_t *)0xF0164 ,		/* ST  */
		(__far uint16_t *)0xF016A ,		/* SOE */
		(__far uint16_t *)0xF0128  		/* SO */
	} ,
	/* ID : 4 */
	{
		(__far uint16_t *)0xF0154 ,		/* SMR_tx */
		(__far uint16_t *)0xF0156 ,		/* SMR_rx */
		(__far uint16_t *)0xF015C ,		/* SCR_tx */
		(__far uint16_t *)0xF015E ,		/* SCR_rx */
		(__far uint16_t *)0xFFF14 ,		/* SDR_tx */
		(__far uint16_t *)0xFFF16 ,		/* SDR_rx */
		(__far uint16_t *)0xF014C ,		/* SIR */
		(__far uint16_t *)0xF0144 ,		/* SSR_tx */
		(__far uint16_t *)0xF0146 ,		/* SSR_rx */
		(__far uint8_t  *)0xF0166 ,		/* SPS */
		(__far uint16_t *)0xF0162 ,		/* SS  */
		(__far uint16_t *)0xF0164 ,		/* ST  */
		(__far uint16_t *)0xF016A ,		/* SOE */
		(__far uint16_t *)0xF0128  		/* SO */
	}
};

const uint8_t bitpos_of_ch_tx[TNUM_UART_CH] = { 0U , 2U , 0U , 2U };
const uint8_t bitpos_of_ch_rx[TNUM_UART_CH] = { 1U , 3U , 1U , 3U };
/*
 * �V���A��I/O�|�[�g�Ǘ��u���b�N�G���A
 */
SIOPCB siopcb_table[TNUM_PORT];

/*
 * �`�����l���������ς݃t���O
 *
 * bss�������őS��false�ɂȂ邱�Ƃ�z�肵�Ă���
 */
bool_t sio_initialized[TNUM_PORT - 1];


Inline bool_t  sio_putready(SIOPCB* siopcb)
{
	const uint16_t ssr_bfe_bit = (0x1U << 5U);
	
	return (sil_reh_mem(siopcb->regaddrs->SSR_tx) & ssr_bfe_bit) == 0 ? true : false;
}

Inline bool_t sio_getready(SIOPCB* siopcb)
{
	const uint16_t ssr_bfe_bit = (0x1U << 5U);
	
	return (sil_reh_mem(siopcb->regaddrs->SSR_rx) & ssr_bfe_bit) == 0 ? true : false;
}

/*
 *  UART�̏�����
 *
 *  �჌�x���o�͂̏������Ń^�[�Q�b�g�ˑ������g�p�ł���悤�ɊO�����J����
 */
void sau_init(uint_t ch)
{
	const SAU_REGADDRS *sau_regaddrs = &sau_register_address_table[ch];
	
	/* �������ς݂̏ꍇ�͂����Ƀ��^�[�� */
	if(sio_initialized[ch] == true)
	{
		return ;
	}
	
	/* SAU�̗L���� */
	sil_wrb_mem( PER0_ADDR, sil_reb_mem( PER0_ADDR ) | 0x04U );
	
	/* SAU�̓����~(SCR,SOE,ST) */
	sil_wrh_mem(sau_regaddrs->ST , ~(0x0005U << ((ch % 2) * 2)));
	sil_wrh_mem(sau_regaddrs->SOE , 
		sil_reh_mem(sau_regaddrs->SOE) & ~(0x0005U << ((ch % 2) * 2)));
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		sil_reh_mem(sau_regaddrs->SCR_rx) & ~0xC000U);
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		sil_reh_mem(sau_regaddrs->SCR_rx) & ~0xC000U);

	/* �g�p�N���b�N�ݒ� */
	sil_wrb_mem(sau_regaddrs->SPS ,
		sil_reb_mem(sau_regaddrs->SPS) & ~(0x0F << SELECT_SPSm * 4) | (PRS_VALUE << SELECT_SPSm * 4));
	
	/* ���M���`���l�����[�h�ݒ� */
	sil_wrh_mem(sau_regaddrs->SMR_tx ,
		  (1U << 0U)           /* MD0   : �o�b�t�@�󂫂Ŋ����ݐM������  */
		| (1U << 1U)           /* MD1,2 : UART���[�h */
		| (0U << 6U)           /* SIS   : ���x�����]���Ȃ� */
		| (0U << 8U)           /* STS   : �\�t�g�E�F�A�g���K */
		| (0U << 14U)          /* CCS   : �]���N���b�N��CKS�r�b�g�őI�� */
		| (SIO_CLOCK << 15U)   /* CKS  :  */
		);	
		
	/* ���M���ʐM����ݒ� */
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		  (1U << 7U)           /* DIR   : MSB�t�@�[�X�g */
		| (1U << 4U)           /* SLC   : �X�g�b�v�r�b�g�Ȃ� */
		| (1U << 2U)           /* Reserved */
		| (3U << 0U)           /* DLS   : 8bit�� */
		);
	
	/* ��M���`���l�����[�h�ݒ� */
	sil_wrh_mem(sau_regaddrs->SMR_rx ,
		  (0U << 0U)           /* MD0   : �]�������Ŋ����ݐM������  */
		| (1U << 1U)           /* MD1,2 : UART���[�h */
		| (0U << 6U)           /* SIS   : ���x�����]���Ȃ� */
		| (0U << 8U)           /* STS   : �\�t�g�E�F�A�g���K */
		| (0U << 14U)          /* CCS   : �]���N���b�N��CKS�r�b�g�őI�� */
		| (SIO_CLOCK << 15U)   /* CKS   :  */
		);

	/* ��M���ʐM����ݒ� */
	sil_wrh_mem(sau_regaddrs->SCR_rx , 
		  (1U << 7U)           /* DIR   : MSB�t�@�[�X�g */
		| (1U << 4U)           /* SLC   : �X�g�b�v�r�b�g�Ȃ� */
		| (1U << 2U)           /* Reserved */
		| (3U << 0U)           /* DLS   : 8bit�� */
		);

	/* ��M�t�B���^�ݒ� */
	sil_wrh_mem(NFEN0_ADDR, (1U << (ch * 2U)));
	
	/* �ʐM���x�ݒ�C���8bit�݂̂�ݒ� */
	sil_wrb_mem((__far  uint8_t*)((uint32_t)sau_regaddrs->SDR_tx + 1) , COMM_CLOCK_VALUE << 1);
	sil_wrb_mem((__far  uint8_t*)((uint32_t)sau_regaddrs->SDR_rx + 1) , COMM_CLOCK_VALUE << 1);
	
	
	/* SAU�̓���J�n */
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		sil_reh_mem(sau_regaddrs->SCR_tx) | 0x8000U);
	sil_wrh_mem(sau_regaddrs->SCR_rx , 
		sil_reh_mem(sau_regaddrs->SCR_rx) | 0x4000U);
	sil_wrh_mem(sau_regaddrs->SO , 
		sil_reh_mem(sau_regaddrs->SO) | (1U << ch));
	sil_wrh_mem(sau_regaddrs->SOE , 
		sil_reh_mem(sau_regaddrs->SOE) | (0x0005U << bitpos_of_ch_tx[ch]));
	sil_wrh_mem(sau_regaddrs->SS , (0x0003U << bitpos_of_ch_tx[ch]));
	
	/* �����݋��� */
	clr_int(INTNO_SIO_TX);
	clr_int(INTNO_SIO_RX);
	ena_int(INTNO_SIO_TX);
	ena_int(INTNO_SIO_RX);
	
	sio_initialized[ch] = true;
}



/*
 *  �^�[�Q�b�g�̃V���A��������
 */
void sau_term(uint_t ch)
{
	const SAU_REGADDRS *sau_regaddrs = &sau_register_address_table[ch];

	/* SAU�̖�����(SCR,SOE,ST) */
	sil_wrh_mem(sau_regaddrs->ST , ~(0x0003U << ((ch % 2) * 2)));
	sil_wrh_mem(sau_regaddrs->SOE , 
		sil_reh_mem(sau_regaddrs->SOE) & ~(0x0003U << ((ch % 2) * 2)));
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		sil_reh_mem(sau_regaddrs->SCR_tx) & ~0xC000U);	/* ���M�֎~ */
	sil_wrh_mem(sau_regaddrs->SCR_rx , 
		sil_reh_mem(sau_regaddrs->SCR_rx) & ~0xC000U);	/* ��M�֎~ */
	
	sio_initialized[ch] = false;	
}

/*
 *  �^�[�Q�b�g�̃V���A���I��
 */
void target_usart_term(ID uart_id)
{
	/* USART�̖����� */
	sau_term(uart_id);
	
	/* �����݋֎~ */
	(void)dis_int(INTNO_SIO_TX);
	(void)dis_int(INTNO_SIO_RX);
	/* �����ݗv���N���A */
	(void)clr_int(INTNO_SIO_TX);
	(void)clr_int(INTNO_SIO_RX);

}

/*
 *  SIO������
 */
void sio_initialize(intptr_t exinf)
{
	int i;

	for (i = 0; i < TNUM_PORT; i++) {
		siopcb_table[i].port = i;
		siopcb_table[i].regaddrs = &sau_register_address_table[i];
		siopcb_table[i].exinf = 0;
	}
}

/*
 *  �V���A���I�[�v��
 */
SIOPCB *sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB* siopcb;

	if (siopid > TNUM_PORT) {
		return NULL;
	}
	
	siopcb = GET_SIOPCB(siopid);
	siopcb->exinf = exinf;
	siopcb->port = siopid;

	sau_init(INDEX_PORT(siopid));
	
	return siopcb;
}

/*
 *  �V���A���N���[�Y
 */
void sio_cls_por(SIOPCB *p_siopcb)
{
	sau_term(INDEX_PORT(p_siopcb->port));
}

/*
 *  �����݃n���h��
 */
void sio_isr_tx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);

	if (sio_putready(siopcb)) {
		sio_irdy_snd(siopcb->exinf);
	}
}

void sio_isr_rx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);

	if (sio_getready(siopcb)) {
		sio_irdy_rcv(siopcb->exinf);
	}
}

/*
 *  1�������M
 */
bool_t sio_snd_chr(SIOPCB *siopcb, char c)
{
	const SAU_REGADDRS *sau_regaddrs = siopcb->regaddrs;
	bool_t ret = false;
	
	if (sio_putready(siopcb)) {
		sil_wrb_mem((uint8_t __far *)sau_regaddrs->SDR_tx, (uint8_t)c);
		ret = true;
	}

	return ret;
}

/*
 *  1������M
 */
int_t sio_rcv_chr(SIOPCB *siopcb)
{
	const SAU_REGADDRS *sau_regaddrs = siopcb->regaddrs;
	int_t c = -1;

	if (sio_getready(siopcb)) {
		c = (int)sil_reb_mem((uint8_t __far *)sau_regaddrs->SDR_rx);
	}

	return c;
}

/*
 *  �R�[���o�b�N�̋���
 */
void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		/* ���M�`���l���𓮍싖�� */
		//sil_wrh_mem(sau_regaddrs->SS , 1U << bitpos_of_ch_tx[INDEX_PORT(siopcb->port)]);	
		break;
	case SIO_RDY_RCV:
		/* ��M�`���l���𓮍싖�� */
		//sil_wrh_mem(sau_regaddrs->SS , 1U << bitpos_of_ch_rx[INDEX_PORT(siopcb->port)]);
		break;
	default:
		break;
	}
}

/* 
 *  �R�[���o�b�N�̋֎~
 */
void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	//const SAU_REGADDRS *sau_regaddrs = siopcb->regaddrs;
	
	switch (cbrtn) {
	case SIO_RDY_SND:
		/* ���M�`���l���𓮍�֎~ */
		//sil_wrh_mem(sau_regaddrs->ST , 1U << bitpos_of_ch_tx[INDEX_PORT(siopcb->port)]);	
		break;
	case SIO_RDY_RCV:
		/* ��M�`���l���𓮍�֎~ */
		//sil_wrh_mem(sau_regaddrs->ST , 1U << bitpos_of_ch_rx[INDEX_PORT(siopcb->port)]);
		break;
	default:
		break;
	}
}

/*
 *  1�����o�́i�|�[�����O�ł̏o�́j
 */
void sio_pol_snd_chr(char c, ID siopid)
{
	const SAU_REGADDRS *sau_regaddrs = siopcb_table[INDEX_PORT(siopid)].regaddrs;
	
	while((sil_reh_mem(sau_regaddrs->SSR_tx) & (0x1U << 5)) != 0 )
		;
	
	sil_wrb_mem((uint8_t __far *)sau_regaddrs->SDR_tx, (uint8_t)c);
}

/*
 *  �჌�x��1�����o��
 */
void sau_log_output(uint_t ch, char c)
{
	const SAU_REGADDRS *sau_regaddrs = siopcb_table[ch].regaddrs;
	
	while((sil_reh_mem(sau_regaddrs->SSR_tx) & (0x1U << 5)) != 0 )
		;
	
	sil_wrb_mem((uint8_t __far *)sau_regaddrs->SDR_tx, (uint8_t)c);
}
 
