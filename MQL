#======================================================================
#
# NAME:  MQL::SOAP
#
# DESC:  
#
# HIST:
#
#======================================================================
# Copyright 2003 - Technology Resource Group LLC as an unpublished work
# For info email bhess@techrg.com
#======================================================================
package MQL::SOAP;

use strict;

BEGIN {
   if($ENV{MQL_SOAP_DEBUG}) {
      use SOAP::Lite +trace => qw(debug);      
   }
   else {
      use SOAP::Lite;      
   }
}

use Config;
use File::Basename;
use MIME::Entity;
use Digest::MD5 qw(md5 md5_hex md5_base64);
use File::Glob;
use vars qw(@EXPORT);


#----------------------------------------------------------------------
# Global Internal Variables
#----------------------------------------------------------------------
my $Handle  = undef;
my $Context = undef;




#======================================================================
#
# NAME:  open
#
# DESC:  Connect to the eMatrix Database server
#
# ARGS:  bootstrap - The name of the bootstrap file
#                    typically located in the MATRIXHOME directory
#        path      - The path to the scripts directory where the 
#                    mql executable resides
#        host      - Hostname of the SOAP Server
#        port      - Port the SOAP Server is running on
#
# RET:   $rc     - The Return code (non-zero means error)
#
# HIST:  
#
#======================================================================
sub open {
   my ($bootstrap, $path, $host, $port) = @_;

   my $return_info = {-rc     => 0,
                      -output => [],
                      -error  => []};


   #------------------------------------------------------------
   # Check if SOAP should be used...
   #------------------------------------------------------------
   if(! $MQL::SOAP::Handle) {      
      $MQL::SOAP::Handle = SOAP::Lite
          -> uri('http://'.$host.':'.$port.'/MQL_SOAP')
          -> proxy('http://'.$host.':'.$port.'/server')
          -> on_fault(sub{});
   }


   if($MQL::SOAP::Handle) {
      my $call = $MQL::SOAP::Handle->call(connect => $bootstrap, $path);
         
      if($call) {
         $return_info = $call->result();
      }
      else {
         $return_info->{-rc} = 1;
         push(@{$return_info->{-output}}, "ERROR"); 
         push(@{$return_info->{-error}}, 
              $MQL::SOAP::Handle->transport->status());
      }
   }
   else {
      $return_info->{-rc} = 1;
      push(@{$return_info->{-output}}, "ERROR"); 
      push(@{$return_info->{-error}}, "MQL::SOAP::Open - No SOAP handle");
   }
   

   return %$return_info;
}




#======================================================================
#
# NAME:  close
#
# DESC:  Close the Connection to eMatrix
#        For SOAP this is just a pass thru to mimick the MQL::Close
#
# ARGS:  Nothing
#
# RET:   $rc     - The Return code (non-zero means error)
#
# HIST:  
#
#======================================================================
sub close {
   my ($self) = @_;

   return 0;
}




#======================================================================
#
# NAME:  open_log
#
# DESC:  Open an MQL Log file
#        For SOAP this is just a pass thru to mimick the MQL::OpenLog
#
# ARGS:  Log file to open
#
# RET:   $rc     - The Return code (non-zero means error)
#       
# HIST:  
#
#======================================================================
sub open_log {
   my ($self) = @_;

   return 0;
}



#======================================================================
#
# NAME:  close_log
#
# DESC:  Close the MQL Log file
#        For SOAP this is just a pass thru to mimick the MQL::CloseLog
#
# ARGS:  Nothing
#
# RET:   $rc     - The Return code (non-zero means error)
#
# HIST:  
#
#======================================================================
sub close_log {
   my ($self) = @_;

   return 0;
}




#======================================================================
#
# NAME:  execute
#
# DESC:  Execute an MQL query against the eMatrix Database
#
# ARGS:  $mql    - The MQL call itself
#
# RET:   $rc     - The Return code (non-zero means error)
#        @output - The output from the MQL call
#        @error  - Any error messages from the MQL call
#
# HIST:  
#
#======================================================================
sub execute {
   my ($self, $mql) = @_;

   my $return_info = {-rc     => 0,
                      -output => [],
                      -error  => []};
   
   if($MQL::SOAP::Handle) {
      my $call = $MQL::SOAP::Handle->call(execute => $MQL::SOAP::Context->[0],
                                          SOAP::Data->type(base64 => $mql));
      if($call) {
         $return_info = $call->result();
      }
      else {
         $return_info->{-rc} = 1;
         push(@{$return_info->{-output}}, "ERROR"); 
         push(@{$return_info->{-error}}, 
              $MQL::SOAP::Handle->transport->status());
      }
   }
   else {
      $return_info->{-rc} = 1;
      push(@{$return_info->{-output}}, " "); 
      push(@{$return_info->{-error}}, "MQL::SOAP::Execute - No SOAP handle");
   }

   return %$return_info;
}




#======================================================================
#
# NAME:  set_context
#
# DESC:  Set the context to the user requested.  Also sets the global
#        var $soap_context if the MQL call was successful.
#
# ARGS:  $context - Array ref which contains Username, Passwd, Vault
#        $mql     - The straight MQL call to set context (non-SOAP)
#
# RET:   $rc     - The Return code (non-zero means error)
#        @output - The output from the MQL call
#        @error  - Any error messages from the MQL call
#
# HIST:  
#
#======================================================================
sub set_context {
   my ($self, $mql, $context) = @_;

   my $return_info = {-rc     => 0,
                      -output => [],
                      -error  => []};
   
   if($MQL::SOAP::Handle) {
      my $call = $MQL::SOAP::Handle->call(set_context => $context);
      
      if($call) {
         $return_info = $call->result();
      }
      else {
         $return_info->{-rc} = 1;
         push(@{$return_info->{-error}}, 
              $MQL::SOAP::Handle->transport->status());
      }
   }
   else {
      $return_info->{-rc} = 1;
      push(@{$return_info->{-error}}, 
           "MQL::SOAP::set_context - No SOAP handle");
   }
   

   if(! $return_info->{-rc}) {
      my ($p_name, $v_name);
      
      $v_name = (split(/\s+vault\s+/, $return_info->{-output}->[0]))[1];
      $v_name = (split(/\s+person\s+/, $v_name))[0];
      
      $p_name = (split(/\s+person\s+/, $return_info->{-output}->[0]))[1];
      $p_name = (split(/\s+vault\s+/, $p_name))[0];
      
      #-------------------------------------------------------
      # Replace the Context stack with the new Context info
      #-------------------------------------------------------
      $MQL::SOAP::Context = undef;
      $MQL::SOAP::Context->[0]->[0] = $p_name;
      $MQL::SOAP::Context->[0]->[1] = $context->[1];
      $MQL::SOAP::Context->[0]->[2] = $v_name;
   }


   return %$return_info;
}





#======================================================================
#
# NAME:  push_context
#
# DESC:  Push the context to the user requested.  Also sets the global
#        var $soap_context if the MQL call was successful.
#
# ARGS:  $context - Array ref which contains Username, Passwd, Vault
#        $mql     - The straight MQL call to set context (non-SOAP)
#
# RET:   $rc     - The Return code (non-zero means error)
#        @output - The output from the MQL call
#        @error  - Any error messages from the MQL call
#
# HIST:  
#
#======================================================================
sub push_context {
   my ($self, $mql, $context) = @_;

   my $return_info = {-rc     => 0,
                      -output => [],
                      -error  => []};
   
   if($MQL::SOAP::Handle) {
      my $call = $MQL::SOAP::Handle->call(push_context => $context, $mql);
   
      if($call) {
         $return_info = $call->result();
      }
      else {
         $return_info->{-rc} = 1;
         push(@{$return_info->{-error}}, 
              $MQL::SOAP::Handle->transport->status());
      }
   }
   else {
      $return_info->{-rc} = 1;
      push(@{$return_info->{-error}}, 
           "MQL::SOAP::push_context - No SOAP handle");
   }

   
   my $rc     = 
   my @output = @{$return_info->{-output}};
   my @error  = @{$return_info->{-error}};
      
   if(! $return_info->{-rc}) {
      my ($p_name, $v_name);
      
      $v_name = (split(/\s+vault\s+/, $return_info->{-output}->[0]))[1];
      $v_name = (split(/\s+person\s+/, $v_name))[0];
      
      $p_name = (split(/\s+person\s+/, $return_info->{-output}->[0]))[1];
      $p_name = (split(/\s+vault\s+/, $p_name))[0];

      unshift @{$MQL::SOAP::Context}, [$p_name, $context->[1], $v_name];
   }

   return %$return_info;
}




#======================================================================
#
# NAME:  pop_context
#
# DESC:  Pop the context to the user requested.  
#
# ARGS:  $mql     - The straight MQL call to set context (non-SOAP)
#
# RET:   $rc      - The Return code (non-zero means error)
#        @output  - The output from the MQL call
#        @error   - Any error messages from the MQL call
#
# HIST:  
#
#======================================================================
sub pop_context {
   my ($self, $mql) = @_;

   my $return_info = {-rc     => 0,
                      -output => [],
                      -error  => []};
   
   my $old_context = shift @{$MQL::SOAP::Context};

   return %$return_info;
}





#======================================================================
#
# NAME:  print_context
#
# DESC:  Get the context of the current User
#
# ARGS:  $mql     - The straight MQL call to set context (non-SOAP)
#
# RET:   $rc      - The Return code (non-zero means error)
#        @output  - The output from the MQL call
#        @error   - Any error messages from the MQL call
#
# HIST:  
#
#======================================================================
sub print_context {
   my ($self, $mql) = @_;
   
   my $return_info = {-rc     => 0,
                      -output => [],
                      -error  => []};

   push(@{$return_info->{-output}},
        qq(context vault $MQL::SOAP::Context->[0]->[2] ) .
        qq(person $MQL::SOAP::Context->[0]->[0]));
   
   return %$return_info;
}




#======================================================================
#
# NAME:  checkin_bus
#
# DESC:  Build a MIME attachment, and send it up via SOAP
#
# ARGS:  $mql     - The MQL statement to do the attachment
#        $files   - Ref to an Array of filenames
#
# RET:   $rc      - The Return code (non-zero means error)
#        @output  - The output from the MQL call
#        @error   - Any error messages from the MQL call
#
# HIST:  
#
#======================================================================
sub checkin_bus {
   my ($self, $mql, $files) = @_;

   my $mime_part;
   my $md5_check;
   my $return_info = {-rc     => 0,
                      -output => [],
                      -error  => []};

   if($MQL::SOAP::Handle) {
      $mime_part =  
          MIME::Entity->build(Type        => "application/octet-stream",
                              Encoding    => "base64",
                              Path        => $files->[0],
                              Filename    => basename ($files->[0]),
                              Disposition => "attachment");
      if($mime_part) {
         if(open (FILE, qq($files->[0]))) {
            binmode (FILE);
            $md5_check = Digest::MD5->new->addfile(*FILE)->b64digest;
            close FILE;

            #print "\n-------------------\n";
            #print "File         = ", $files->[0], "\n";
            #print "MD5 Checksum = ", $md5_check, "\n";
            #print "-------------------\n";


            my $call = $MQL::SOAP::Handle->parts(($mime_part))->
                call(checkin_bus => $MQL::SOAP::Context->[0], $mql, 
                     $files->[0], $md5_check);

            
            if($call) {
               $return_info = $call->result();
            }
            else {
               $return_info->{-rc} = 1;

               push(@{$return_info->{-error}}, 
                    $MQL::SOAP::Handle->transport->status());
            }
         }
         else {
            $return_info->{-rc} = 1;
            
            push(@{$return_info->{-error}}, 
                 "MQL::SOAP::checkin_bus - Unable to open '$files->[0]'");
         }
      }
      else {
         $return_info->{-rc} = 1;

         push(@{$return_info->{-error}}, 
              "MQL::SOAP::checkin_bus - Cannot create MIME attachment");
      }
   }
   else {
      $return_info->{-rc} = 1;

      push(@{$return_info->{-error}}, 
           "MQL::SOAP::checkin_bus - No SOAP handle");
   }
   
   
   return %$return_info;
}





#======================================================================
#
# NAME:  checkout_bus
#
# DESC:  Recieve MIME Attachements from the SOAP server
#
# ARGS:  $mql     - The MQL statement to do the attachment
#        $files   - Ref to an Array of filenames
#
# RET:   $rc      - The Return code (non-zero means error)
#        @output  - The output from the MQL call
#        @error   - Any error messages from the MQL call
#
# HIST:  
#
#======================================================================
sub checkout_bus {
   my ($self, $mql, $dir) = @_;

   my $return_info = {-rc     => 0,
                      -output => [],
                      -error  => []};
   
   if($MQL::SOAP::Handle) {
      my $som = $MQL::SOAP::Handle->
          checkout_bus($MQL::SOAP::Context->[0], $mql, $dir);

      if($som) {
         my $part = $som->parts->[0];
         
         if($part) {
            $return_info = $som->result;
            
            if(! is_error(@{$return_info->{-output}})) {
               my $bh;
               my $io;
               my $buf;
               
               if(open FILE, qq(> $dir/$return_info->{-file})) {
                  binmode FILE;
                  
                  if($bh = $$part->bodyhandle) {
                     $io = $bh->open;
                     
                     while($io->read($buf, 8192)) {
                        print FILE $buf;
                     }
                     
                     $io->close;
                  }

                  close FILE;
                  
                  open FILE, qq($dir/$return_info->{-file});
                  binmode FILE;
                  my $checksum = Digest::MD5->new->addfile(*FILE)->b64digest;
                  close FILE;
                  
                  if ($return_info->{-checksum} ne $checksum) {
                     #---------------------------------------------
                     # Checksum mismatch
                     #---------------------------------------------
                     $return_info->{-rc} = 1;
                     push(@{$return_info->{-output}},
                          "MQL::SOAP::checkin_bus - MD5 checksum mismatch");
                     push(@{$return_info->{-error}},
                          "MQL::SOAP::checkin_bus - MD5 checksum mismatch");
                  }
               }
               else {
                  $return_info->{-rc} = 1;

                  my $path = qq($dir/$return_info->{-file});
                  push(@{$return_info->{-output}},
                       "MQL::SOAP::checkin_bus - Unable to open '$path'");
                  push(@{$return_info->{-error}},
                       "MQL::SOAP::checkin_bus - Unable to open '$path'");
               }
            }
            else {
               $return_info->{-rc} = 1;

               push @{$return_info->{-error}}, @{$return_info->{-output}};
            }
         }
         else {
            $return_info->{-rc} = 1;

            push(@{$return_info->{-error}}, 
                 "MQL::SOAP::checkout_bus - Cannot get MIME attachment");
         }
      }
      else {
         $return_info->{-rc} = 1;

         push(@{$return_info->{-error}}, 
              $MQL::SOAP::Handle->transport->status());
      }
   }
   else {
      $return_info->{-rc} = 1;

      push(@{$return_info->{-error}}, 
           "MQL::SOAP::checkout_bus - No SOAP handle");
   }
   
   return %$return_info;
}



#======================================================================
# NAME:  is_error() 
#
# DESC:  Parses the Output from an MQL command, looking for either
#        "Error:", "System Error:", or "Warning:".  If any are found
#        returns 1
#
# ARGS:  Output  - Array of output from an MQL command
#
# RET:   Error code (0|1)
#
# HIST:  
#
#======================================================================
sub is_error {
   my ($self, $mql, $dir) = @_;

   my $code;
   my $ERROR = 0;

   foreach (@_) {
      chomp;

      if ($_ =~ /^Error: \#(\d+)\: (.*)$/) {
         $code = $1;
         #push @MQL_ERROR, qq(# $code : $2);
         $ERROR = 1;
      }

      elsif ($_ =~ /^System Error: \#(\d+)\: (.*)$/) {
         $code = $1;
         #push @MQL_ERROR, qq(# $code : $2);
         $ERROR = 1;
      }

      elsif ($_ =~ /^Warning: \#(\d+)\: (.*)$/) {
         $code = $1;
         # push @MQL_ERROR, qq(# $code : $2);
         # $ERROR = 1;
      }
   }

   return $ERROR;
}


#======================================================================
# End of MQL::SOAP
#======================================================================
1;
