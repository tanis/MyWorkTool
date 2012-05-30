#!/usr/bin/perl
# --*-- coding:utf-8 --*--
use strict;

use Encode;
use CGI qw/:standard/;
use MediaWiki::API;
use WWW::Bugzilla;

#binmode(STDOUT, ":encoding(utf-8)");


sub get_wiki_page
{
    my ($page_title)=@_;

    my $mw = MediaWiki::API->new();
    $mw->{config}->{api_url} = 'http://192.168.0.164/mediawiki/api.php';

    $mw->login( 
        {
            lgname => 'your_name',
            lgpassword => 'your_pass',
            lgdomain => 'your_domain'
        } )
        || die $mw->{error}->{code} . ': ' . $mw->{error}->{details};
    
    my $article = $mw->api( {
        action => 'query',
        prop => 'revisions',
        rvprop => 'content',
        titles => $page_title,
        redirect => 1,
                            }
        )
        || die $mw->{error}->{code} . ': ' . $mw->{error}->{details};
    
    my $refpages =  $article->{query}->{pages};
    my %pages = %$refpages;
    my ($pageid) = keys %pages;
    $mw->logout();
    return $pages{$pageid}->{revisions}[0]->{'*'};
}


sub chompline
{
    my ($in) = @_;
    return $1 if ($in =~ /^\s*(.+?)\s*$/);
    return $in;
}


sub addbug
{
    my ($prod, $comp,$title,$desc) = @_;
    print
        "Trying add bug: <br />\n",
        "&nbsp;&nbsp;$prod&nbsp;=>&nbsp;$comp<br />\n",
        "&nbsp;&nbsp;Summary: $title<br />\n",
        "&nbsp;&nbsp;Desc:<br />\n",
        "&nbsp;&nbsp;&nbsp;&nbsp;$desc<br />\n<br />\n";

    my $bz = WWW::Bugzilla->new( server => '192.168.0.164/bugzilla',
                                 email => 'your_email',
                                 password => 'your_pass',
        );

    $bz->product($prod);
    $bz->component($comp);
    $bz->priority('P3');
    #summary => decode('utf-8', $title),
    $bz->summary($title);
    #description => decode('utf-8', $desc),
    $bz->description($desc);
    $bz->severity(decode('utf-8', "工作任务"));
    my $bug_number = $bz->commit;

    print "Submitted bug id is : $bug_number<br />\n";

    $bz->change_status("assigned");
    $bz->commit;

    print "Modify it to assigned.<p />\n";
}



print header(-type =>'text/html', -charset => 'utf-8'),
    start_html("Create init tasks");

my %map = (
"SPDM" => "1-SPDM",
"APP" => "2-APP",
"BSP" => "3-BSP",
"RF" => "4-RF",
"BB" => "5-BB"
);

my $script = <<END_OF_JAVASCRIPT
<script language="JavaScript"> 
<!-- 
function onSubmit()
{
    var btn = document.getElementById("submitbtn");
    btn.disabled=true;
    btn.value = "创建中...";
    return true;
}
//-->
</script>
END_OF_JAVASCRIPT
;
if (param('hiddenparam') eq 'submitted')
{
    my $prod = param('product');
    #my $prod = 'UP812C';
    my $page = get_wiki_page('Product bug init template');

    my @lines = split("[\r\n]+", $page);

    my @bugs=();

    foreach my $line (@lines)
    {
        if ($line =~ /\|\s*(.+)?\s*\|\|\s*(.+)?\s*\|\|\s*(.+)?\s*/)
        {
            my $comp_simple = uc(chompline($1));
            my $title = chompline($2);
            my $desc = chompline($3);
            my $comp;
            if (exists $map{$comp_simple} )
            {
                $comp = $map{$comp_simple};
            }
            else
            {
                die "Error Your $comp_simple is not fit.\n";
            }
            my %bug = ();
            $bug{'title'} = $title;
            $bug{'comp'} = $comp;
            $bug{'desc'} = $desc;
            push @bugs, \%bug;
        }
    }

    foreach my $bug (@bugs)
    {
        if (0)
        {
            print "prod : ", $prod, "<br />\n";
            print "comp : ", $bug->{'comp'}, "<br />\n";
            print "title: ", $bug->{'title'}, "<br />\n";
            print "desc : ", $bug->{'desc'}, "<br />\n";
        }
        else
        {
            addbug $prod, $bug->{'comp'}, $bug->{'title'}, $bug->{'desc'};
        }
        print "<br />\n";
    }
}
else
{
    my $bz = WWW::Bugzilla->new( server => '192.168.0.164/bugzilla',
                                 email => 'your_email',
                                 password => 'your_pass',
        );    
    my @prods = $bz->available('product');
#    my @prods = qw/A B C/;

    print "$script\n";

    print
        start_form( -onSubmit => 'return onSubmit();'),
        hr,
        "请选择产品，将自动创建在",
        a( {href => "http://192.168.0.164/mediawiki/index.php/Product_bug_init_template"},"这个模板里"),
        "定义的项目初始事项",
        br,
        "请注意：需提前在bugzilla上建立项目的产品、子产品结构",
        hr,
        "产品名称",
        popup_menu( -name => 'product',
                    -value => [@prods]),
        p,"\n",
        hidden( -name => 'hiddenparam',
                -value => 'submitted'),"\n",
        submit ( -id => 'submitbtn',
                 -value => '创建'),
        end_form,"\n",
        hr,"\n";
}
print end_html;
