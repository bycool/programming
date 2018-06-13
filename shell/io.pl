#! /usr/bin/perl -w

# delta storage path for disk stat
my $delta_path = "/home/teanee/workstation/install-fzs-src/run";
# stat every 15 sec
my $int_stat = 2;
my $full_flag = 0;

while (1) {
	$dt = `date`;
	$del = `du -h --max-depth=0 $delta_path`;
	$io = `iostat -x | grep -v "^Linux"`;
	chop ($io);
	print "$dt";
	print "$del";
	print "$io";
	print "-----------------------------\n";

	$full = `ps -ef | grep full | grep -v grep | wc -l`;
	if ($full_flag == 0 and $full > 0) {
		$full_flag = 1;
		print "FULL SYNC START at $dt\n";
	}	
	if ($full_flag == 1 and $full == 0) {
		$full_flag = 2;
		print "FULL SYNC END at $dt\n";
	}
	
	sleep ($int_stat);
}
