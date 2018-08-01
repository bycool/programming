#! /usr/bin/perl -w

my $base = "./data-s/";
my $total = 0;
my $year;
my $month;
my $day;
my $lmt = 105*1024*1024;
my @W = ('0' .. '9', 'a' .. 'z', 'A' .. 'Z');
my $dida = 1;

sub randstr {
    my $len = shift;
    my $str;
    my $i = 1;
    while ($i++ < $len) {
        $str .= $W[rand(@W)];
    }
    return $str;
}

my $counter = 1;
while (1) {
	$year = int (rand (18)) + 2000;
	$month = int (rand (11)) + 1;
	$day = int (rand (29)) + 1; 
	$no = int (rand (399)) + 1;
	my $fname = $base.$year."/".$month."/".$day."/".$no.".txt";
	if (-e $fname) {
		my $str = randstr (64);
		`echo $str >> $fname`;
		#print "Add \"$str\" to $fname.\n";
		$dida ++;
	}
	$total += 64;		
	if ($dida == 16*1024) {
		$dida = 1;
		print "$counter MegaBytes  added to files under $base.\n";
		$counter ++;
	}
	exit (0) if ($total > $lmt);
}
