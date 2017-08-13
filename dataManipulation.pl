#!/usr/bin/perl

use strict;
use warnings;
 
my $filename = "test.txt";

open(my $fh, '<:encoding(UTF-8)', $filename)
	or die "Could not open file '$filename' $!";
 
while (my $row = <$fh>) {
	chomp $row;
	my $rowCopy = substr($row, 0, 9);		# Search by just the course code not including the description
	if($rowCopy =~ /(^[A-Z])*\d\d\d\d/) {	# Regular Expression filtering out the other lines
		print "$row\n";						# Printing to the terminal, used > 'file.txt' to get output in file
	}
}

print "done\n";