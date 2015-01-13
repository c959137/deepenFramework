<?php
/**
* @file  
* 框架主檔
*/

/**
* 系統框架類別
*/
class applicationFramework
{
	const KEY_APPLICATION_UID = 'APPLICATION_UID';			///< 系統編號鍵值 
	const KEY_RESOURCES_DATA = 'DATA_RESOURCES';			///< 資源目錄鍵值 
	const KEY_RESOURCES_CONFIG = 'CONFIG_RESOURCES';		///< 設定目錄鍵值 
	const KEY_RESOURCES_LOGGER = 'LOGGER_RESOURCES';		///< 紀錄目錄鍵值 
	
	private static $_staticParams = [];
	
	
	/**
	* @brief 取得系統編號
	* @return string 
	* @author nico chen 2015-01-07
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-07</b>    
	*      - 建立函數			
	*/
	public function applicationUid()
	{
		return (isset($_SERVER[self::KEY_APPLICATION_UID])) ? $_SERVER[self::KEY_APPLICATION_UID] : '';
	}
	
	/**
	* @brief 取得資源資料目錄
	* @param array $dirList 相對位置的目錄陣列
	* @code
    *   # 範例		
	* 	['a', 'b', 'c'] => $RESOURCES/a/b/c
	* 
	* @endcode
	* @return string 
	* @author nico chen 2015-01-07
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-07</b>    
	*      - 建立函數			
	*   <b>- nico chen / 2015-01-08</b>    
	*      - 將取得資料, 驗證抽出變成共用函式 applicationFramework::resourcePathExecute
	*/
	public static function resourcesDataPath(array $dirList = [])
	{
		return static::resourcePathExecute(self::KEY_RESOURCES_DATA, $dirList);
	}

	/**
	* @brief 取得資源紀錄檔目錄
	* @param array $dirList 相對位置的目錄陣列
	* @code
    *   # 範例		
	* 	['a', 'b', 'c'] => $RESOURCES/a/b/c
	* 
	* @endcode
	* @return string 
	* @author nico chen 2015-01-07
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-07</b>    
	*      - 建立函數			
	*   <b>- nico chen / 2015-01-08</b>    
	*      - 將取得資料, 驗證抽出變成共用函式 applicationFramework::resourcePathExecute
	*/
	public static function resourcesLoggerPath(array $dirList = [])
	{
		return static::resourcePathExecute(self::KEY_RESOURCES_LOGGER, $dirList);
	}

	/**
	* @brief 檢查指定的資源路徑是否存在, 如果不存在是否自動建立
	* @param string $resourceKey 代表資源鍵值
	* @code
	* 	applicationFramework::KEY_RESOURCES_LOGGER 
	* 	applicationFramework::KEY_RESOURCES_CONFIG 
	* 	applicationFramework::KEY_RESOURCES_DATA 
	* @endcode
	* @param array $dirList 相對位置的目錄陣列
	* @code
    *   # 範例		
	* 	['a', 'b', 'c'] => $RESOURCES/a/b/c
	* 
	* @endcode
	* @return string 資源路徑
	* @author nico chen 2015-01-08
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-08</b>    
	*      - 建立函數			
	*/
	protected static function resourcePathExecute($resourceKey, array $dirList = [])
	{
		if (!isset(static::$_staticParams['resources'][$resourceKey])) {
			static::$_staticParams['resources'][$resourceKey] = isset($_SERVER[$resourceKey]) ? $_SERVER[$resourceKey] : '';
			if (static::$_staticParams['resources'][$resourceKey] == '') {
				throw new exception('環境變數 : ' . $resourceKey . '尚未設定');
			}
			static::$_staticParams['resources'][$resourceKey] .=  DIRECTORY_SEPARATOR . static::applicationUid() . DIRECTORY_SEPARATOR;
		}
		$path = static::$_staticParams['resources'][$resourceKey];
		if (!empty($dirList)) {
			$path .= implode(DIRECTORY_SEPARATOR, $dirList);
		}
		static::pathChecker($path, true);
		return $path;
	}
	
	/**
	* @brief 取得資源設定檔目錄
	* @param array $dirList 相對位置的目錄陣列
	* @code
    *   # 範例		
	* 	['a', 'b', 'c'] => $RESOURCES/a/b/c
	* 
	* @endcode
	* @return string 
	* @author nico chen 2015-01-07
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-07</b>    
	*      - 建立函數			
	*   <b>- nico chen / 2015-01-08</b>    
	*      - 將取得資料, 驗證抽出變成共用函式 applicationFramework::resourcePathExecute
	*/
	public static function resourcesConfigPath(array $dirList = [])
	{
		return static::resourcePathExecute(self::KEY_RESOURCES_CONFIG, $dirList);
	}

	/**
	* @brief 執行指定的方法, 確定這個方法的時間成本
	* @param string $methodName 方法名稱
	* @param integer $count 每次執行次數
	* @param integer $stepCount 總共執行幾次
	* @return array 
	* @code
	*   // 執行 static::resourcesLoggerPath() 方法, 每次跑5000遍, 跑 10 次
	*	applicationFramework::methodSpeedTest('resourcesLoggerPath', 50000, 10)

		// 回傳值格式
		[
			0 => float 0.18627214431763
			1 => float 0.19444799423218
			2 => float 0.17987489700317
			3 => float 0.17764210700989
			4 => float 0.19061017036438
			5 => float 0.174889087677
			6 => float 0.18867087364197
			7 => float 0.19216108322144
			8 => float 0.18187594413757
			9 => float 0.17446899414062
			'total' => float 1.8409132957458
			'cnt' => int 10
			'average' => float 0.18409132957458
		]
	* @endcode
	*
	* @author nico chen 2015-01-07
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-07</b>    
	*      - 建立函數			
	*/
	public function methodSpeedTest($methodName, $count = 9999, $stepCount = 1)
	{
		$times = [];
		while ($stepCount > 0) {
			$counting = $count;
			$s = microtime(true);
			while ($counting > 0) {
				applicationFramework::$methodName();
				$counting--;
			}
			$times[] = microtime(true) - $s;
			$stepCount--;
		}
		$total = 0;
		$cnt = 0;
		foreach ($times as $sec) {
			$total += $sec;
			$cnt++;
		}
		$times['total'] = $total;
		$times['cnt'] = $cnt;
		$times['average'] = $total / $cnt;
		return $times;
	}
	
	public static function pathChecker($path, $createDir = false)
	{
		if (file_exists($path)) {
			return true;
		}
		if (!$createDir) {
			return false;
		}
		
		$umask = umask(0002);
		$flag = @mkdir($path, 0774, true);
		umask($umask);
		/*
		0664 => drw-r--r--
		0774 => drwxr-xr--
		*/
		return $flag;
	}
}
