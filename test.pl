#!/usr/local/perl/bin/perl

use strict;
use MQL;

my $rc;

my $DB_DELIM = "|";

my $mql = $ARGV[0];
$mql = qq(list type) if ! $mql;

my $times = $ARGV[1];
$times = 1 if ! $times;

print "MQL   = $mql\n";
print "TIMES = $times\n";


#----------------------------------------------------------------------
# Open MQL session
#----------------------------------------------------------------------
$rc = MQL::Open();
print "MQL::Open returned '$rc' " . localtime()  . "\n";
exit if $rc;



#----------------------------------------------------------------------
# Start MQL Log
#----------------------------------------------------------------------
$rc = MQL::OpenLog("test.log");
print "MQL::OpenLog returned '$rc' " . localtime()  . "\n";

my @output;
my @error;

MQL::Execute(qq(set context person creator vault "eService Production"));

for(1..$times) {
   ($rc, @output, @error) = MQL::Execute($mql);

   my $olines = scalar @output;
   my $elines = scalar @error;
   
   #------------------------------------------------------------
   # Print output
   #------------------------------------------------------------
   print "MQL::Execute returned '$rc' " . localtime()  . "\n";
   print "\n\nMQL::Execute Output: "    . localtime()  . "\n";

   foreach (@output) {
      print "$_\n";
   }

   print "MQL::Execute Output DONE\n";
   
   #------------------------------------------------------------   
   # Print errors
   #------------------------------------------------------------   
   print "\n\nMQL::Execute Error: " . localtime()  . "\n";

   foreach (@error) {
      print "$_\n";
   }

   print "MQL::Execute Error DONE\n\n";

   print "OUTPUT LINES = $olines\n";
   print "ERROR  LINES = $elines\n\n\n";
}



#----------------------------------------------------------------------
# Close Log and MQL session
#----------------------------------------------------------------------
$rc = MQL::CloseLog();
print "MQL::CloseLog returned '$rc' " . localtime()  . "\n";


$rc = MQL::Close();
print "MQL::Close returned '$rc' " . localtime()  . "\n";

