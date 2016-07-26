#! /usr/bin/perl
#==============================
#
# struct2dot
#
# 2016/07/21 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
#==============================

sub remove_white_space {
	my ($p) = @_;

	$$p = $1 if ($$p =~ /^\s+(.*)/s);
}

sub pickup_region {
	my ($p, $start, $end) = @_;
	my $pos = index($$p, $end) + length($end);
	my $ret;

	return if (substr($$p, 0, length($start)) ne $start);

	$ret = substr($$p, 0, $pos);

	$$p = substr($$p, $pos);

	return $ret;
}

sub pickup_sub_region {
	my ($p, $start, $end) = @_;
	my $ret;

	$ret = pickup_region($p, $start, $end);
	$ret = substr($ret, 0, length($ret) - length($end));
	$ret = substr($ret, length($start));

	return $ret;
}

sub remove_comment {
	my ($p) = @_;

	$$p =~ s/\/\*[\s\S]*?\*\/|\/\/.*//g;

	$$p =~ s/#ifdef[\s\S]*?#endif//g;
}

sub set_label {
	my ($name, $line) = @_;
	my ($lable);

	if ($$line =~ /struct\s+(\S*)\s+.*$/) {
		$lable = $1;
	} else {
		return;
	}

	$$line = "<$lable>$$line";

	$link = $link . "$name:$lable -> $lable [color = blue, lhead = cluster_$lable];\n";
}

sub push_out {
	my ($out , $next) = @_;

	if ($$out eq "") {
		$$out = $next;
	} else {
		$$out = "$$out|$next";
	}
}

sub print_struct {
	my ($name) = @_;
	my ($struct, $line);
	my (@member);
	my ($out, $sub);

	pickup_region(\$file, "struct", $name);
	remove_white_space(\$file);

	$struct = pickup_sub_region(\$file, "{", "};");
	remove_white_space(\$struct);

	print("\tsubgraph cluster_$name {\n");
	print("\t	label = $name;\n");
	print("\t	labelloc = t;\n");
	print("\t	labeljust = l;\n");
	print("\t	fillcolor = \"#77ccff\";\n");
	print("\n");

	print("\t	$name [label = \"");
	@member = split(/;/, $struct);

	$out = "";
	foreach $line (@member) {
		remove_white_space(\$line);
		$line =~ s/\t/ /g;
		last if ($line eq "");
		set_label($name, \$line);
		push_out(\$out, $line);
	}
	$out = "{$out}";
	print("$out\"];\n");

	print("\t};\n\n");
}

sub print_non_struct {
	my ($i_comma) = index($file, ";");
	my ($line) = substr($file, 0, $i_comma);
	my ($name);

	return if ($i_comma < 0);

	$name = $1 if ($line =~ /\S\s+(\S*)/);

	$file = substr($file, $i_comma + 1);

	print("\t$name [label = \"$line\"]\n\n");
}

die "can't open file\n" if !open(R, $ARGV[0]);
local $/ = undef;
$file = <R>;
close(R);

remove_comment(\$file);

print "
digraph struct_graph {
	graph [style = filled, compound = true];
	node [shape = record];

";


$link = "";
while (length($file)) {
	remove_white_space(\$file);

	if ($file =~ /^struct\s+(\S*)\s*{/) {
		print_struct($1);
	} else {
		print_non_struct();
	};
}

print "$link
}
";
