#!/usr/bin/perl
use strict;

# �L�[���[�h
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
	
	# �������Q�łȂ���΃G���[
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
			# �Z�N�V�����֘A�̐�����ύX
			$section_no += 1;
			$sub_section_no = 0;
			$subsub_section_no = 0;
			$subsub_definition_no = 0;
			$subsubsub_definition_no = 0;
			
			# �Z�N�V���������̏�������
			$line =~ s/$kwd_section_lv1/$section_no\. /;
		}
		elsif($line =~ /$kwd_section_lv2/)
		{
			# �Z�N�V�����֘A�̐�����ύX
			$sub_section_no += 1;
			$subsub_section_no = 0;
			$subsub_definition_no = 0;
			$subsubsub_definition_no = 0;
			
			# �Z�N�V���������̏�������
			$line =~ s/$kwd_section_lv2/$section_no\.$sub_section_no /;
		}
		elsif($line =~ /$kwd_section_lv3/)
		{
			# �Z�N�V�����֘A�̐�����ύX
			$subsub_section_no += 1;
			$subsub_definition_no = 0;
			$subsubsub_definition_no = 0;
			
			# �Z�N�V���������̏�������
			$line =~ s/$kwd_section_lv3/$section_no\.$sub_section_no\.$subsub_section_no /;
		}
		elsif($line =~ /$kwd_definition_lv3/)
		{
			# �Z�N�V�����֘A�̐�����ύX
			$subsub_definition_no += 1;
			$subsubsub_definition_no = 0;
			
			# �Z�N�V���������̏�������
			$line =~ s/$kwd_definition_lv3/\($section_no-$sub_section_no-$subsub_definition_no\) /;
		}
		elsif($line =~ /$kwd_definition_lv4/)
		{
			# �Z�N�V�����֘A�̐�����ύX
			$subsubsub_definition_no += 1;
			
			# �Z�N�V���������̏�������
			$line =~ s/$kwd_definition_lv4/\($section_no-$sub_section_no-$subsub_section_no-$subsubsub_definition_no\) /;
		}
		elsif($line =~ /$kwd_reset/)
		{
			# �S�Ă̏�Ԃ����Z�b�g
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

# �G���g���|�C���g
sub main($$)
{
	my @input;
	my @output;
	
	if(!check_arg())
	{
		exit(-1);
	}
	
	# �t�@�C���I�[�v��
	my $file_in = shift;
	my $file_out = shift;
	
	open(IN , "<$file_in") or die("[input file] is not exist.\n");
	if(!open(OUT , ">$file_out"))
	{
		close(IN);
		die("[output file] is not exist.\n");
	}
	
	# �t�@�C����S�ēǂݎ��
	@input = <IN>;
	my $result = assign(\@input);
	
	print OUT @$result;
	
	# �t�@�C���N���[�Y
	close(IN);
	close(OUT);
	
}


main($ARGV[0] , $ARGV[1]);
