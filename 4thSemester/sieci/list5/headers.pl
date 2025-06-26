use HTTP::Daemon;
use HTTP::Status;  
#use IO::File;

my $d = HTTP::Daemon->new(
        LocalAddr => '127.0.0.1',
        LocalPort => 5678,
    )|| die;

print "<URL:", $d->url, ">\n";

while (my $c = $d->accept) {
    while (my $r = $c->get_request) {
        if ($r->method eq 'GET') {
            my $headers = $r->headers_as_string;
            $c->send_response(
                HTTP::Response->new(
                    RC_OK,
                    'OK',
                    [ 'Content-Type' => 'text/plain' ],
                    $headers
                )
            );
        }
        else {
            $c->send_error(RC_FORBIDDEN)
        }
    }
    $c->close;
    undef($c);
}
