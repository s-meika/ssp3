#!/usr/bin/perl
use strict;

# キーワード
my $kwd_section_lv1 = "\\(section\\)";
my $kwd_section_lv2 = "\\(sub-section\\)";
my $kwd_section_lv3 = "\\(subsub-section\\)";

my $kwd_definition_lv3 = "\\(subsub-definition\\)";
my $kwd_definition_lv4 = "\\(subsubsub-definition\\)";

my $kwd_reset = "\\(reset\\)";

sub usage()
{
	print $0 . " [input file] [output file]\n";
	print "\tNotice:If [output file] exist , $0 overwrite it.\n";
}

sub check_arg()
{
	my $precond = 1;
	
	# 引数が２つでなければエラー
	if($#ARGV != 1)
	{
		usage();
		$precond = 0;
	}
	
	return $precond;
}

sub assign($)
{
	my $data = shift;
	my @output;
	
	my $section_no = 0;
	my $sub_section_no = 0;
	my $subsub_section_no = 0;
	
	my $subsub_definition_no = 0;
	my $subsubsub_definition_no = 0;
	
	foreach my $line(@$data)
	{
		if($line =~ /$kwd_section_lv1/)
		{
			# セクション関連の数字を変更
			$section_no += 1;
			$sub_section_no = 0;
			$subsub_section_no = 0;
			$subsub_definition_no = 0;
			$subsubsub_definition_no = 0;
			
			# セクション部分の書き換え
			$line =~ s/$kwd_section_lv1/$section_no\. /;
		}
		elsif($line =~ /$kwd_section_lv2/)
		{
			# セクション関連の数字を変更
			$sub_section_no += 1;
			$subsub_section_no = 0;
			$subsub_definition_no = 0;
			$subsubsub_definition_no = 0;
			
			# セクション部分の書き換え
			$line =~ s/$kwd_section_lv2/$section_no\.$sub_section_no /;
		}
		elsif($line =~ /$kwd_section_lv3/)
		{
			# セクション関連の数字を変更
			$subsub_section_no += 1;
			$subsub_definition_no = 0;
			$subsubsub_definition_no = 0;
			
			# セクション部分の書き換え
			$line =~ s/$kwd_section_lv3/$section_no\.$sub_section_no\.$subsub_section_no /;
		}
		elsif($line =~ /$kwd_definition_lv3/)
		{
			# セクション関連の数字を変更
			$subsub_definition_no += 1;
			$subsubsub_definition_no = 0;
			
			# セクション部分の書き換え
			$line =~ s/$kwd_definition_lv3/\($section_no-$sub_section_no-$subsub_definition_no\) /;
		}
		elsif($line =~ /$kwd_definition_lv4/)
		{
			# セクション関連の数字を変更
			$subsubsub_definition_no += 1;
			
			# セクション部分の書き換え
			$line =~ s/$kwd_definition_lv4/\($section_no-$sub_section_no-$subsub_section_no-$subsubsub_definition_no\) /;
		}
		elsif($line =~ /$kwd_reset/)
		{
			# 全ての状態をリセット
			$section_no = 0;
			$sub_section_no = 0;
			$subsub_section_no = 0;
			$subsub_definition_no = 0;
			$subsubsub_definition_no = 0;
			
			$line = "";
		}
		else
		{
			# Nothing to do
		}
		
		push @output , $line;
	}
	
	return \@output;
}

# エントリポイント
sub main($$)
{
	my @input;
	my @output;
	
	if(!check_arg())
	{
		exit(-1);
	}
	
	# ファイルオープン
	my $file_in = shift;
	my $file_out = shift;
	
	open(IN , "<$file_in") or die("[input file] is not exist.\n");
	if(!open(OUT , ">$file_out"))
	{
		close(IN);
		die("[output file] is not exist.\n");
	}
	
	# ファイルを全て読み取り
	@input = <IN>;
	my $result = assign(\@input);
	
	print OUT @$result;
	
	# ファイルクローズ
	close(IN);
	close(OUT);
	
}


main($ARGV[0] , $ARGV[1]);
