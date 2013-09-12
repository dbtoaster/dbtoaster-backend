<?

function parse($file) {
	$res=[];
	$tmp=null; // name,toM3,toSC,toBC,avg,min,max,mem_pre,mem_post,mem_time
	$n="([0-9,.]+)";
	foreach(explode("\n",file_get_contents($file)) as $l) {
		if (preg_match('/--------------- (.*)/',$l,$m)) {
			if ($tmp!=null) $res[]=$tmp; $tmp=[$m[1]];
		}
		else if (preg_match('/SQL -> M3      : +'.$n.'/',$l,$m)) $tmp[1]=$m[1];
		else if (preg_match('/Scala codegen  : +'.$n.'/',$l,$m)) $tmp[2]=$m[1];
		else if (preg_match('/Scala compile  : +'.$n.'/',$l,$m)) $tmp[3]=$m[1];
		else if (preg_match('/Scala running  : +'.$n.' \[ *'.$n.', *'.$n.'\] \(sec\)/',$l,$m)) {
			$tmp[4]=$m[1];
			$tmp[5]=$m[2];
			$tmp[6]=$m[3];
		} else if (preg_match('/\[(Full )?GC '.$n.'K->'.$n.'K\([0-9]+K\), '.$n.'/',$l,$m)) {
			//  K'.$n.' secs\]
			$tmp[7]=max(round($m[2]/(1024*1024),3),@doubleval($tmp[7]));
			$tmp[8]=max(round($m[3]/(1024*1024),3),@doubleval($tmp[8]));
			$t = doubleval(str_replace(",",".",$m[4]))/10; // because 10 runs
			if (isset($tmp[9])) $tmp[9]+=$t; else $tmp[9]=$t;
		}
	}
	$res[]=$tmp;
	foreach($res as $r) { for ($i=0;$i<count($r);$i++) echo @$r[$i].","; echo "\n"; }
}

parse('tpch-big_del.txt');
parse('finance-huge.txt');


?>
