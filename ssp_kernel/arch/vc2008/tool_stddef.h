/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2007 by Meika Sugimoto
 * 
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
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
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 */

/*
 *  t_stddef.hの開発環境依存部（VC2008用）
 *
 *  このインクルードファイルは，t_stddef.h の先頭でインクルードされる．
 *  他のファイルからは直接インクルードすることはない．他のインクルード
 *  ファイルに先立って処理されるため，他のインクルードファイルに依存し
 *  てはならない．
 */

#if !defined( TOPPERS_TOOL_STDDEF_H )
#define TOPPERS_TOOL_STDDEF_H

/*
 *  コンパイラの拡張機能のためのマクロ定義
 */
/*
 *  inline 識別子はコンパイラがサポートしているため，コメントアウトとする．
 *  なお，inline を _inline に変換したい場合，コンパイルオプションにて
 *  "-fnot_reserve_inline"を指定し，その上で以下の記載を有効にすること．
 */
#define	inline		_inline
#define	Inline		_inline

/*
 *  asm 識別子はコンパイラがサポートしているため，コメントアウトとする．
 *  なお，asm を _asm に変換したい場合，コンパイルオプションにて
 *  "-fnot_reserve_asm"を指定し，その上で以下の記載を有効にすること．
 */
/*#define	asm		_asm	*/
#define	Asm		_asm

/*
 *  リターンしない関数
 */
#define NoReturn


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
#include <stddef.h>
#include <limits.h>
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  stdint.hの代用となる定義
 *
 *  開発環境にstdint.hが用意されておらず，各整数型のサイズがあるパター
 *  ンに当てはまる場合に，stdint.hの代用となる定義を与える．
 *
 *  TOPPERS_STDINT_TYPE1: char/short/int/long longのビット長がそれぞれ
 *                        8/16/32/64ビットで，ポインタのビット長がlong
 *                        のビット長と一致する場合
 */

/*
 *  コンパイラ依存のデータ型の定義
 */
#ifndef TOPPERS_MACRO_ONLY

typedef signed char			int8_t;		/* 符号付き8ビット整数 */
typedef unsigned char		uint8_t;	/* 符号無し8ビット整数 */

typedef signed short		int16_t;	/* 符号付き16ビット整数 */
typedef unsigned short		uint16_t;	/* 符号無し16ビット整数 */

typedef signed long			int32_t;	/* 符号付き32ビット整数 */
typedef unsigned long		uint32_t;	/* 符号無し32ビット整数 */

typedef signed long long	int64_t;	/* 符号付き64ビット整数 */
typedef unsigned long long	uint64_t;	/* 符号無し64ビット整数 */

#endif /* TOPPERS_MACRO_ONLY */

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
 *  コンパイラ依存のデータ型に格納できる最大値と最小値の定義
 */
#define INT8_MAX			SCHAR_MAX
#define INT8_MIN			SCHAR_MIN
#define UINT8_MAX			UCHAR_MAX

#define INT16_MAX			SHRT_MAX
#define INT16_MIN			SHRT_MIN
#define UINT16_MAX			USHRT_MAX

#define INT32_MAX			LONG_MAX
#define INT32_MIN			LONG_MIN
#define UINT32_MAX			ULONG_MAX

#define INT64_MAX			LLONG_MAX
#define INT64_MIN			LLONG_MIN
#define UINT64_MAX			ULLONG_MAX

/*
 *  空ラベルの定義
 *    Visual Studioでは大きさゼロの配列はコンパイルエラーになるため、
 *    ここで別途定義する。
 */
#define TOPPERS_EMPTY_LABEL(x,y) x y[1]


#endif /* TOPPERS_TOOL_STDDEF_H */

