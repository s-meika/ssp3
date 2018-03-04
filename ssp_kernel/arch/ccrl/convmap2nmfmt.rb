#!/usr/bin/env ruby
# -*- coding: utf-8 -*-
#
#  Copyright (C) 2017 by Meika Sugimoto
#
#  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
#
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
#
#

#
#  CS+のマップファイルをGNU NM形式に変換するためのスクリプト
#


module CSPlusConstants
	SymbolStartMarker = "\\*\\*\\* Symbol List \\*\\*\\*"
	SectionStartMarker = "SECTION="
	SymbolNameIndex = 2
	SymbolAddressIndex = 2
	SymbolAttribute = "T"
end

# デバッグメッセージフラグ
DebugMessageOn = false


def PutDebugMessage( str )
	if DebugMessageOn == true then
		puts str
	end
end


#
# メインクラス
#

class ConvCSPlusMap2GnuNM
	@mapfile = ""
	@outfile = ""
 	@symbols = {}
	@lines = {}
	
	def initialize()
		# 引数数のチェック
		# PutDebugMessage( "引数の数:#{ARGV.length}" )
		
		if( ARGV.length != 2 ) then
			print "引数エラー:\n"
			put_usage()
			exit( -1 )
		end
		
		# マップファイル名取得
		@mapfile = ARGV[0]
		PutDebugMessage( "Map file name : #{@mapfile}" )
		# 出力ファイル名取得
		@outfile = ARGV[1]
		PutDebugMessage( "Output file name : #{@outfile}" )
		
		@symbols = Array.new()
		@lines = Array.new()
	end
	
	#
	#  マップファイルの読み込み
	#
	def	ReadMapFile
		begin
			File.open( @mapfile ) do | file |
				file.read.split( "\n" ).each do | line |
					@lines.push line
				end
			end
		
		rescue SystemCallError => e
			puts %Q(class=[#{e.class}] message=[#{e.message}])
			exit( -1 )
		rescue IOError => e
			puts %Q(class=[#{e.class}] message=[#{e.message}])
			exit( -1 )
		end
		
	end
	
	#
	#   読み込んだマップファイルのパース＆変換
	#
	def ConvertFormat
		current = 0
		
		PutDebugMessage( "Total lines of #{@mapfile} : " + @lines.length.to_s )
		
		#
		#  シンボル情報の始まりまでスキップする
		#
		start_symbol = false
		while start_symbol == false do
		
			if @lines.length < current then
				puts "No symbol information in #{@mapfile}."
				exit( -1 )
			end
			
			if @lines[ current ] =~ /#{CSPlusConstants::SymbolStartMarker}/ then
				PutDebugMessage( 'Symbol infomation marker found at line:' + ( current + 1 ).to_s + '.' )
				start_symbol = true
			end
			
			current += 1
		end
		
		#
		#  行を解析してシンボル情報を追加
		#
		
		# セクション指定個所を探す
		eof_found = false
		while eof_found == false do
		
			if @lines.length < current then
				eof_found = true
				
			elsif @lines[ current ] =~ /#{CSPlusConstants::SectionStartMarker}/ then
				PutDebugMessage( 'Section infomation marker found at line:' + ( current + 1 ).to_s + '.' )
				
				current += 3	# 3行進める(セクション情報を捨てる)
				
				#
				# シンボル定義は以下のフォーマットで空行でシンボル記述が終了する
				#
				#     <Symbol>
				#            <Address>    <size>   <attribute> ,<scope>   * 
				#
				
				# Symbolを見つける
				symbol_found = false
				section_end = false
				while symbol_found == false do
					words = @lines[ current ].split( /(\s+|,)/ )
					PutDebugMessage( "line : " + ( current + 1 ).to_s + ' num of words ' + words.length.to_s + '.' )
					if( words.length == 3 ) then
						PutDebugMessage( 'First symbol found \'' + words[CSPlusConstants::SymbolNameIndex] + '\'.' )
						symbol_found = true
					elsif words.empty? == true then
						PutDebugMessage( 'Section end at line : ' + ( current + 1 ).to_s + '.' )
						section_end = true
						symbol_found = true
					else
						current += 1
					end
				end
				
				# 空行が出てくるまでシンボル定義を解析
				while section_end == false do
					if( @lines[ current ].empty? == true )
						section_end = true
					else
						# シンボル情報を生成してリストに追加
						symbolname = @lines[ current ].split( /(\s+|,)/ )[CSPlusConstants::SymbolNameIndex]
						symbolinfo = @lines[ current + 1 ].split( /(\s+|,)/ )
						
						@symbols.push( MapSymbol.new( 
												symbolname ,
												symbolinfo[CSPlusConstants::SymbolNameIndex] ,
												CSPlusConstants::SymbolAttribute ) ) 
						
						current += 2
					end
				end
				
				
			end
			
			current += 1
		end
		
		PutDebugMessage( "Parse finished." )
		
	end
	
	#
	#   GNU NM形式シンボルファイルの出力
	#
	def OutputMapFile
		PutDebugMessage( "Write symbol information to \'#{@outfile}\'" )
		begin
			File.open( @outfile , "w" ) do | file |
				# シンボル情報をNM形式にして出力
				@symbols.each do | sym |
					file.printf( "%8s\t%s\t%s\n" , sym.getAddress() , sym.getAttribute() , sym.getName() )
				end
			end
		rescue SystemCallError => e
			puts %Q(class=[#{e.class}] message=[#{e.message}])
			exit( -1 )
		rescue IOError => e
			puts %Q(class=[#{e.class}] message=[#{e.message}])
			exit( -1 )
		end
	end
	
	def put_usage
		print $0 + " "
		print <<EOS
<map file path> <output file path>
EOS
	end
	
end

#
# シンボル管理クラス
#
class MapSymbol
	@name = ""
	@address = ""
	@attribute = ""
	
	def initialize( n , ad , at )
		@name = n
		@address = ad
		@attribute = at
	end
	
	def getName()
		return @name
	end
	
	def getAddress()
		return @address
	end
	
	def getAttribute()
		return @attribute
	end
	
end

#
#  メイン処理
#

main = ConvCSPlusMap2GnuNM.new()

main.ReadMapFile()
main.ConvertFormat()
main.OutputMapFile()


