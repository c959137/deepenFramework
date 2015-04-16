<?php
/**
* @file  
* 框架主檔
*/

namespace m5D02F22739AA11E4B3C6005056847E34;

require 'traits/propertysClass.inc';
require 'instanceClass.inc';
require 'traits/arrayPathClass.inc';
require 'traits/fileUtilsClass.inc';

/**
* 系統框架類別
*/
class applicationFrameworkClass 
{
	use traits\propertysClass, instanceClass, traits\fileUtilsClass;
	
	const KEY_APPLICATION_UID = 'APPLICATION_UID';				///< 系統編號鍵值 
	const KEY_RESOURCES_DATA = 'DATA_RESOURCES';				///< 資源目錄鍵值 
	const KEY_RESOURCES_CONFIG = 'CONFIG_RESOURCES';			///< 設定目錄鍵值 
	const KEY_RESOURCES_LOGGER = 'LOGGER_RESOURCES';			///< 紀錄目錄鍵值 
	const RESOURCES_DEVELOP_MARK = 'RESOURCES_DEVELOP_MARK';	///< 資源路徑開發標籤
	
	CONST RUN_MODE_WEB = 'web';
	CONST RUN_MODE_CONSOLE = 'console';
	
	private static $_staticParams = [];
	
	private $_instanceParams = [];
	
	/**
	* @brief 取得系統編號
	* @return string 
	* @author nico chen 2015-01-07
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-07</b>    
	*      - 建立函數			
	*/
	public static function applicationUid()
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
			$resourcesDevelopMark = isset($_SERVER[self::RESOURCES_DEVELOP_MARK]) ? $_SERVER[self::RESOURCES_DEVELOP_MARK] : '';
			static::$_staticParams['resources'][$resourceKey] .=  DIRECTORY_SEPARATOR . static::applicationUid() . $resourcesDevelopMark . DIRECTORY_SEPARATOR;
		}
		$path = static::$_staticParams['resources'][$resourceKey];
		if (!empty($dirList)) {
			foreach ($dirList as $subPath) {
				if (!$subPath) {
					continue;
				}
				$path .= $subPath . DIRECTORY_SEPARATOR; 
			}
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
	
	/**
	* @brief 輸出版本資訊
	*/
	public static function version()
	{
		die('版本編號 1.00');
	}
	
	/**
	* @brief 載入指定的類別
	* @param string $className 類別名稱
	* @param string $middleNs 中間的命名空間 
	* @param string $moduleUid 模組編號
	* @return string 完整的類別名稱
	*/
	public static function classLoader($className, $middleNs = '', $moduleUid = '5D02F22739AA11E4B3C6005056847E34')
	{
		$moduleClass = static::moduleClassLoader($moduleUid);
		return $moduleClass::classLoader($className, $middleNs);
	}
	
	/**
	* @brief 載入指定的模組管理類別
	* @param string $moduleUid 模組編號
	* @return string 模組類別
	*/
	public static function moduleClassLoader($moduleUid = '5D02F22739AA11E4B3C6005056847E34')
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = [];
		}
		if (!$moduleUid) {
			$moduleUid = '5D02F22739AA11E4B3C6005056847E34';
		}
		if (!isset(self::$_staticParams[$keyName][$moduleUid])) {
			$moduleKeyName = 'MODULE_' . $moduleUid;
			if(!isset($_SERVER[$moduleKeyName])) {
				throw new \exception("指定的模組 [{$moduleUid}] 設未設定");
			}
			$rootPath = $_SERVER[$moduleKeyName];
			if (substr($rootPath, -1) != DIRECTORY_SEPARATOR) {
				$rootPath .= DIRECTORY_SEPARATOR;
			}
			$fn = $rootPath . 'moduleManagerClass.inc';
			if (!file_exists($fn)) {
				throw new \exception("指定的模組管理檔案  {$moduleUid} - moduleManagerClass.inc 不存在");
			}
			require $fn;
			
			$className = "m{$moduleUid}\\moduleManagerClass";
			if (!class_exists($className)) {
				throw new \exception("指定的模組類別 [{$className}] 不存在");
			}
			self::$_staticParams[$keyName][$moduleUid] = [
				'file' => $fn,
				'className' => $className,
			];
		}
		return self::$_staticParams[$keyName][$moduleUid]['className'];
	}
	
	/**
	* @brief 執行的模式
	* @return string 
	* @author nico chen 2015-01-22
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-22</b>    
	*      - 建立函數			
	*/
	public static function runMode()
	{
		return isset($_SERVER['SERVER_PROTOCOL']) ? self::RUN_MODE_WEB : self::RUN_MODE_CONSOLE;
	}
	
	/**
	* @brief 取得所有的模組編號設定
	* @param string $path 
	* @return string 
	* @author nico chen 2015-01-23
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-23</b>    
	*      - 建立函數			
	*/
	protected static function modulePathList()
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			$list = [];
			foreach ($_SERVER as $name => $value) {
				if (strpos($name, 'MODULE_') === false) {
					continue;
				}
				$list[substr($name, 7, 999)] = $value;
			}
			uasort($list, function($path1, $path2){
				$len1 = strlen($path1);
				$len2 = strlen($path2);
				if ($len1 == $len2) {
					return 0;
				}
				return $len1 < $len2;
			});
			self::$_staticParams[$keyName] = $list;
		}
		return self::$_staticParams[$keyName];
	}
	
	/**
	* @brief 取得某路徑所在的模組編號
	* @param string $path 
	* @return string 
	* @author nico chen 2015-01-23
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-23</b>    
	*      - 建立函數			
	*/
	public static function moduleUidByPath($path)
	{
		$root = dirname($path);
		$modulePathList = static::modulePathList();
		foreach ($modulePathList as $moduleUid => $path) {
			if (strpos($root, $path) === 0) {
				return $moduleUid;
			}
		}
		return null;
	}
	
	/**
	* @brief 取得某路徑所在的模組類別
	* @param string $path 
	* @return string 
	* @use moduleClassLoader
	* @author nico chen 2015-01-23
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-23</b>    
	*      - 建立函數			
	*/
	public static function moduleClassLoaderByPath($path)
	{
		$moduleUid = static::moduleUidByPath($path);
		if (empty($moduleUid)) {
			throw new \exception("指定的路徑不在模組內");
		}
		return static::moduleClassLoader($moduleUid);
	}
}
