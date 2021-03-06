<?php
/**
* @file  
* 暫時放置, 有時間再分類
*/
/**
* @brief 設定中斷點, 為了方便使用所以封裝了 backtraceTools::xxx
* @param string $msg 中斷點說明
* @author nico chen 2015-01-08
* @version 0.00.01
* \b CHANGE \b HISTORY: <br>	 
*   <b>- nico chen / 2015-01-08</b>    
*      - 建立函數			
*/
function xxx($msg = '')
{
	$backtraceToolsClass = m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('backtraceToolsClass');
	$backtraceToolsClass::xxx($msg, __FUNCTION__, '');
}


/**
* @brief 產出 uuid
* @param boolean $longCode true 產出長碼, false 產出短碼
* @code
	// 長碼
	// 57EC4BA1-1369-E2A9-AA5C-000056369B0A
  
	// 短碼
	// 57EC4BA11369E2A9AA5C000056369B0A
* @endcode
* @author nico chen 2015-01-22
* @version 0.00.01
* \b CHANGE \b HISTORY: <br>	 
*   <b>- nico chen / 2015-01-22</b>    
*      - 建立函數			
*/
function uuid($longCode = false)
{
	$template = ($longCode) ? '%08x-%04x-%04x-%02x%02x-%012x' : '%08x%04x%04x%02x%02x%012x';
   // version 4 UUID
   $uuid = sprintf(
	   $template,
	   mt_rand(),
	   mt_rand(0, 65535),
	   bindec(substr_replace(
		   sprintf('%016b', mt_rand(0, 65535)), '0100', 11, 4)
	   ),
	   bindec(substr_replace(sprintf('%08b', mt_rand(0, 255)), '01', 5, 2)),
	   mt_rand(0, 255),
	   mt_rand()
   );
  return strtoupper ($uuid);
}

if (!defined('UUID_NULL')) {
	define('UUID_NULL', '00000000000000000000000000000000');
	define('UUID_NULL_LONG', '00000000-0000-0000-0000-000000000000');
};

function uuidNull($longCode = false)
{
	return $longCode ? UUID_NULL_LONG : UUID_NULL;
	static $data = '00000000-0000-0000-0000-000000000000';
	return $longCode ? $data : str_replace('-', '', $data);
}

/*
	uuid 格式確認, 只要符合長或短格式, 都傳回 true, 否則都傳回否.
**/
function uuidChecker($value)
{
	return preg_match('/^[0-9a-f]{32}$|^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$/im', $value);
}

function showScript($script)
{
	$runMode = m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::runMode();
	switch ($runMode) {
		case m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::RUN_MODE_WEB :
			echo "<pre>{$script}</pre>";
			break;
			
		default : 
			echo "\n{$script}\n";
			break;
	}
}

function showArray(array $data)
{
	$runMode = m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::runMode();
	switch ($runMode) {
		case m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::RUN_MODE_WEB :
			echo '<pre>', print_r($data, true), '</pre>';
			break;
			
		default : 
			echo '\n' . print_r($data, true) . '\n';
			break;
	}
	
}

/**
	將 unicode escape 得字串轉為 utf-8
	@code
		$a = '#U6240#U5f97#U5206#U914d#U3001GDP#U8207#U7d93#U6fdf#U6210#U9577.DOC';
		echo asc2unicode($a);
		
		所得分配、GDP與經濟成長.DOC
		
	@endcode
*/
function asc2unicode($asciiData)
{
	return  preg_replace_callback('/#[uU]([0-9a-f]{4})/im', function ($match) {
		return mb_convert_encoding(pack('H*', $match[1]), 'UTF-8', 'UCS-2BE');
	}, $asciiData);	
}

/**
	字串轉布林
*/
function strToBool($value, $defaultValue = false)
{
	if (is_bool($value)) {
		return $value;
	}
	
	if (is_string($value)) {
		return preg_match('/^t(rue)?|on|open|1|y(es)?$/im', $value);
	} else if (is_numeric($value)) {
		return $value!=0;
	} else {
		return $defaultValue;
	}
}

/**
	取出指定序列中的指定的起點與數量陣列
	
	param integet $totalPages 總頁數
	param integer $currentIndex 目前頁數
	patam integer $btnCount 按鍵個數
	
*/
function pageBtnList($totalPages, $currentIndex, $btnCount = 10)
{
	if ($totalPages < 1) {
		throw new \exception("頁數小於一");
	}
	if ($currentIndex >= $totalPages) {
		throw new \exception("索引值超過總數");
	}

	$pageBtnList = [
		$currentIndex => [
			'selected' => true
		]
	];
	$averageBtnCount = floor(($btnCount - count($pageBtnList)) / 2);
	$lIndex = $currentIndex;
	$lCount = $averageBtnCount;
	while ($lCount > 0) {
		$lIndex--;
		if ($lIndex < 0) {
			break;
		}
		$pageBtnList[$lIndex] = [];
		$lCount--;
	}

	$rIndex = $currentIndex;
	$rCount = $btnCount - count($pageBtnList);
	while ($rCount > 0) {
		$rIndex++;
		if ($rIndex >= $totalPages) {
			break;
		}
		$pageBtnList[$rIndex] = [];
		$rCount--;
	}

	while (($lCount > 0) && (count($pageBtnList) <  $btnCount)) {
		$rIndex++;
		if ($rIndex >= $totalPages) {
			break;
		}
		$pageBtnList[$rIndex] = [];
		$lCount--;
	}
	
	while (($rCount > 0) && (count($pageBtnList) <  $btnCount)) {
		$lIndex--;
		if ($lIndex < 0) {
			break;
		}
		$pageBtnList[$lIndex] = [];
		$rCount--;
	}

	ksort($pageBtnList);
	return $pageBtnList;
}

/*
	取出指定序列中的指定的起點與數量陣列
	
	param integet $totalPages 總頁數
	param integer $currentIndex 目前頁數
	patam integer $btnCount 按鍵個數


	pageBtnList2(5, 2, 10);
	pageBtnList2(8, 2, 10);
	pageBtnList2(20, 2, 10);
	
**/
function pageBtnList2($totalPages, $currentIndex, $btnCount = 10)
{
	$difference = 1;
	$sign = -1;
	$showTime = [
		$currentIndex => [
			'selected' => true,
		]
	];
	$minItem = 1;
	$maxItem = $totalPages;
	
	$minOver = false;
	$maxOver = false;

	 while(count($showTime) < $btnCount && ($minOver==false || $maxOver ==false))
	 {
		 $addItem = $currentIndex + ($difference * $sign);
		 if ($addItem < $minItem) {
			 $minOver = true;
		 } else if ($addItem > $maxItem) {
			 $maxOver = true;
		 } else {
			$showTime[$addItem] = [];
		 }
		 $difference += ($sign == 1) ? 1 : 0;
		 $sign *= -1;
	 }
	ksort($showTime);
	return $showTime;
}

function implodeUrl(array $urlComponents)
{
	$maps = [
		'scheme' => '://',
		'user' => //':',
			function($name, $info){
				if (!isset($info['pass'])) {
					return '';
				}
				return $info[$name] . ':';
			},
		'pass' => //'@',
			function($name, $info){
				if (!isset($info['user'])) {
					return '';
				}
				return $info[$name] . '@';
			},
		'host' => '',
		'port' => 
			function($name, $info){
				$defaultPort = ($info['scheme'] == 'http') ? '80' : '443';
				return $info[$name] == $defaultPort ? '' : ':' . $info[$name];
			},
		'path' => '',
		'query' => //'',
			function($name, $info){
				return '?' . $info[$name];
			},
		'fragment' => //'',
			function($name, $info){
				return '#' . $info[$name];
			},
	];
	$url = '';
	foreach ($maps as $k => $v) {
		if (!isset($urlComponents[$k])) {
			continue;
		}
		$value = is_callable($v) ? $v($k, $urlComponents) : $urlComponents[$k] . $v;
		$url .= $value;
	}
	return $url;
}

/*
	取得陣列路徑的值, 如果沒有指定的路徑則回傳預設值
**/
function pathValue(array $data, $path = '', $defaultValue = null)
{
		$pathInfo = explode('/', $path);
		$cmd = '';
		foreach ($pathInfo as $k) {
			if (!$k) {continue;};
			$cmd .= "['{$k}']";
		}
		$cmd = "return isset(\$data{$cmd}) ? \$data{$cmd} : \$defaultValue;";
		return eval($cmd);
}