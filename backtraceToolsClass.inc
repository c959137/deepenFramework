<?php
/**
* @file  
* 程式追蹤
*/

namespace m5D02F22739AA11E4B3C6005056847E34;

/**
* 中斷點追蹤工具類別
*/
class backtraceToolsClass {
	/**
	* @brief 設定中斷點
	* @param string $msg 中斷點說明
	* @param string $function 呼叫中斷點的函式名稱
	* @param string $class 呼叫中斷點的類別名稱
	*
	* @code
		# 呈現結果
		檔案名稱 : /home/c959137/chroot/html/1CA9603A916B11E4AD1C22000B368196/deepen/utils.inc
		程式行數 : 157
		Array
		(
			[0] => Array
				(
					[file] => /home/c959137/chroot/html/1CA9603A916B11E4AD1C22000B368196/deepen/utils.inc
					[line] => 68
					[function] => pathChecker
					[class] => applicationFramework
					[type] => ::
					[args] => Array
						(
							[0] => /home/c959137/chroot/resources/logger/1CA9603A916B11E4AD1C22000B368196/
						)

				)

			[1] => Array
				(
					[file] => /home/c959137/chroot/html/1CA9603A916B11E4AD1C22000B368196/www/loader.php
					[line] => 13
					[function] => resourcesLoggerPath
					[class] => applicationFramework
					[type] => ::
					[args] => Array
						(
							[0] => Array
								(
									[0] => a
									[1] => b
									[2] => c
								)

						)

				)

		)	
	* @endcode
	* @author nico chen 2015-01-08
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-08</b>    
	*      - 建立函數			
	*/
	public static function  xxx($msg = '', $function = __FUNCTION__, $class = __CLASS__) 
	{
		$traceInfoList = debug_backtrace();
		while (true) {
			$traceInfo = array_shift($traceInfoList);		
			if (!$traceInfo) {
				break;
			}
			
			if ($traceInfo['function'] != $function) {
				continue;
			} else {
				if ($class=='') {
					if (isset($traceInfo['class'])) {
						continue;
					}
				} else {
					if (!isset($traceInfo['class'])) {
						continue;
					}
					if ($traceInfo['class'] != $class) {
						continue;
					}
				}
			};
			break;
		}
		echo "XXX<br/>程式中斷<hr/>";
		if (isset($traceInfo['file'])) {
			echo "檔案名稱 : {$traceInfo['file']}<br/>";
		}
		if (isset($traceInfo['line'])) {
			echo "程式行數 : {$traceInfo['line']}<br/>";
		}
		if ($msg) {
			if (is_string($msg)) {
				echo "中斷訊息 : {$msg}<br/>";
			} else {
				echo print_r($msg, true);
			}
		}
		echo '<pre>';
		print_r($traceInfoList);
		echo '</pre>';
		die();
	}
	
	/**
	* @brief 顯示陣列內容
	* @param array $arrayInfo
	* @author nico chen 2015-01-08
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-08</b>    
	*      - 建立函數			
	*/
	public static function show (array $arrayInfo)
	{
		foreach ($traceInfo as $keyName => $value) {
			echo $keyName, ' => ';
			if (is_string($value)) {
				echo $value;
			} else if (is_numeric($value)) {
				echo $value;
			} else if (is_array($value)) {
				static::show($value);
			} else if (is_objedct($value)) {
				echo get_class($value);
			}
			echo '<br/>';
		}
	}
}
