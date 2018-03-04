/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2017 by Meika Sugimoto
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */

/*
 *		RL78/G13マイコン依存の定義
 */

#ifndef TOPPERS_RL78_G13_H
#define TOPPERS_RL78_G13_H

#define RL78_G13_INTNO_MIN		(0)
#define RL78_G13_INTNO_MAX		(53)

/*
 *  割込みベクタ番号定義
 */
#define INTWDTI			(0)
#define INTLVI			(1)
#define INTP0			(2)
#define INTP1			(3)
#define INTP2			(4)
#define INTP3			(5)
#define INTP4			(6)
#define INTP5			(7)
#define INTST2			(8)
#define INTCSI20		(8)
#define INTIIC20		(8)
#define INTSR2			(9)
#define INTCSI21		(9)
#define INTIIC21		(9)
#define INTSRE2			(10)
#define INTTM11H		(10)
#define INTDMA0			(11)
#define INTDMA1			(12)
#define INTST0			(13)
#define INTCSI00		(13)
#define INTIIC00		(13)
#define INTSR0			(14)
#define INTCSI01		(14)
#define INTIIC01		(14)
#define INTSRE0			(15)
#define INTTM01H		(15)
#define INTST1			(16)
#define INTCSI10		(16)
#define INTIIC10		(16)
#define INTSR1			(17)
#define INTCSI11		(17)
#define INTIIC11		(17)
#define INTSRE1			(18)
#define INTTM03H		(18)
#define INTIICA0		(19)
#define INTTM00			(20)
#define INTTM01			(21)
#define INTTM02			(22)
#define INTTM03			(23)
#define INTAD			(24)
#define INTRTC			(25)
#define INTIT			(26)
#define INTKR			(27)
#define INTST3			(28)
#define INTCSI30		(28)
#define INTIIC30		(28)
#define INTSR3			(29)
#define INTCSI31		(29)
#define INTIIC31		(29)
#define INTTM13			(30)
#define INTTM04			(31)
#define INTTM05			(32)
#define INTTM06			(33)
#define INTTM07			(34)
#define INTP6			(35)
#define INTP7			(36)
#define INTP8			(37)
#define INTP9			(38)
#define INTP10			(39)
#define INTP11			(40)
#define INTTM10			(41)
#define INTTM11			(42)
#define INTTM12			(43)
#define INTSRE3			(44)
#define INTTM13H		(44)
#define INTMD			(45)
#define INTIICA1		(46)
#define INTFL			(47)
#define INTDMA2			(48)
#define INTDMA3			(49)
#define INTTM14			(50)
#define INTTM15			(51)
#define INTTM16			(52)
#define INTTM17			(53)



#endif /* TOPPERS_RL78_G13_H */
