use strict;
use warnings;
use JSON::XS;

my $outdir = "Outdir";
my $target =
'https://opendata.hauts-de-seine.fr/explore/dataset/fr-229200506-plans-de-carrieres/download/?format=json';
my $body = qx{curl -s $target};    # DO NOT DO THAT PLEASE
die "Couldn't get $target" unless defined $body;

my $planches = decode_json $body;

mkdir $outdir;
foreach my $planche (@$planches) {
    my $fname = $outdir . "/" . $planche->{'fields'}->{'fichier'}->{'filename'};
    my $path =
"https://opendata.hauts-de-seine.fr/explore/dataset/fr-229200506-plans-de-carrieres/files/"
      . $planche->{'fields'}->{'fichier'}->{'id'}
      . "/download/";

    if ( -e $fname ) {
        next;
    }
    qx{curl --progress-bar $path --output $fname};
    printf "DL    %s\n", $fname;
}
