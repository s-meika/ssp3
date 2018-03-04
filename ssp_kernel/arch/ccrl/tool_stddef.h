/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2016 by Meika Sugimoto
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
 *		t_stddef.hの開発環境依存部（CC-RL用）
 */

#ifndef TOPPERS_TOOL_STDDEF_H
#define TOPPERS_TOOL_STDDEF_H

/*
 *  コンパイラの拡張機能のためのマクロ定義
 */
#ifndef __cplusplus					/* C++にはinline がある */
#if __STDC_VERSION__ < 199901L		/* C99にはinline がある */
#define inline	 __inline			/* インライン関数 */
#endif /* __STDC_VERSION__ < 199901L */
#endif /* __cplusplus */

#define Inline		static __inline	/* インライン関数 */

#ifndef __cplusplus					/* C++にはasmがある */
#define asm		__asm__				/* インラインアセンブラ */
#endif /* __cplusplus */

#define Asm		__asm /* インラインアセンブラ（最適化抑止）*/

#define NoReturn
									/* リターンしない関数 */

/*
 *  開発環境の標準インクルードファイルの利用
 *
 *  NULLの定義をstddef.hから，INT_MAX，INT_MIN，UINT_MAX，LONG_MAX，
 *  LONG_MIN，ULONG_MAX，CHAR_BITの定義をlimits.hから取り込む．
 *
 *  C++/EC++では，標準仕様上はこれらのインクルードファイルが用意されて
 *  いるとは限らないので注意が必要である（ほとんどの開発環境で用意され
 *  ている）．
 */
#ifndef TOPPERS_MACRO_ONLY
#include <stdint.h>
#include <limits.h>
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  CCRLではC99をサポートしているため，stdint.hの代用となる定義は不要
 *
 */

/*
 *  コンパイラ依存のデータ型の整数定数を作るマクロ
 */
#ifndef INT8_C
#define INT8_C(val)			(val)
#endif /* INT8_C */

#ifndef UINT8_C
#define UINT8_C(val)		(val ## U)
#endif /* UINT8_C */

#ifndef INT16_C
#define INT16_C(val)		(val)
#endif /* INT16_C */

#ifndef UINT16_C
#define UINT16_C(val)		(val ## U)
#endif /* UINT16_C */

#ifndef INT32_C
#define INT32_C(val)		(val)
#endif /* INT32_C */

#ifndef UINT32_C
#define UINT32_C(val)		(val ## U)
#endif /* UINT32_C */

#ifndef INT64_C
#define INT64_C(val)		(val ## LL)
#endif /* INT64_C */

#ifndef UINT64_C
#define UINT64_C(val)		(val ## ULL)
#endif /* UINT64_C */

/*
 *  CCRLではC99をサポートしているため，コンパイラ依存のデータ型に格納できる最大値と最小値の定義の定義は不要
 */


/*
 *  浮動小数点型に関する定義
 *
 *  TOPPERS_STDFLOAT_TYPE1: floatがIEEE754準拠の単精度浮動小数点数，
 *							doubleが倍精度浮動小数点数の場合
 */
#ifdef TOPPERS_STDFLOAT_TYPE1
#ifndef TOPPERS_MACRO_ONLY

typedef float		float32_t;			/* IEEE754準拠の単精度浮動小数点数 */
typedef double		double64_t;			/* IEEE754準拠の倍精度浮動小数点数 */

#endif /* TOPPERS_MACRO_ONLY */

#define FLOAT32_MIN		1.17549435e-38F
#define FLOAT32_MAX		3.40282347e+38F
#define DOUBLE64_MIN	2.2250738585072014e-308
#define DOUBLE64_MAX	1.7976931348623157e+308

#endif /* TOPPERS_STDFLOAT_TYPE1 */

/*
 *  空ラベルの定義
 *    Visual Studioでは大きさゼロの配列はコンパイルエラーになるため、
 *    ここで別途定義する。
 */
#define TOPPERS_EMPTY_LABEL(x,y) x y[1]

#endif /* TOPPERS_TOOL_STDDEF_H */
