<?php
namespace m5D02F22739AA11E4B3C6005056847E34\traits;
trait arrayPathClass 
{
	/**
	* @brief 將路徑轉換為陣列的索引
	* @param string $path 路徑
	* @return mixed 
	* @code
    *   # 範例		
	* 	pathToArrayKey('/a/b/c')
	* 	[
			'namespace' => 'a',
			'accessCmd' => '->b->c'
	*	]
	* 
	* @endcode
	
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	protected static function pathToArrayKey($path)
    {
		if (empty($path)) {
			throw new exception ("路徑不允許空值");
		}
		$list = explode('/', preg_replace('%[/]{2,}%im', '/', $path));

		$cmd = '';
		foreach ($list as $keyName) {
			if ($keyName === '') {
				continue;
			}
			$cmd .= "['{$keyName}']";
		};
		return $cmd;
    }
	
	protected static function valueSet (array &$list, $path, $value) 
	{
		$arrayKey = static::pathToArrayKey($path);
		$cmd = '$list' . $arrayKey . ' = $value;';
		eval ($cmd);
	}

	protected static function valueGet (array $list, $path, $defaultValue = null) 
	{
		$arrayKey = static::pathToArrayKey($path);
		$data = '$list' . $arrayKey;
		$value = $defaultValue;
		$cmd = '$value = isset(' . $data . ') ? ' . $data . ' : $defaultValue;';
		eval ($cmd);
		return $value;
	}
	
	public static function sessionEmpty($path)
	{
		$zendSessionKey = static::pathToZendSessionKey($path);
		$sessionInstance = new Zend_Session_Namespace($zendSessionKey['namespace']);
		$cmd = 'unset($sessionInstance' . $zendSessionKey['accessCmd'] . ');';
		eval($cmd);
	} 	
	
	
	protected static function arrayToPath()
	{
		$list = [];
		$args = func_get_args();
		foreach ($args as $arg) {
			if (is_array($arg)) {
					$list = array_merge($list, $arg);
			} else {
				$list = array_merge($list, explode(DIRECTORY_SEPARATOR, $arg));
			};
		}
		$fullPath = '';
		foreach ($list as $path) {
			if (!$path) {
				continue;
			}
			if ($fullPath != '') $fullPath .= DIRECTORY_SEPARATOR; 
			$fullPath .= $path;
		}
		$fullPath = DIRECTORY_SEPARATOR . $fullPath;
		return $fullPath;
	}
	
	protected static function pathToArray($path)
	{
		var_dump (explode('\\', $path));
		xxx();
	}
	
	protected static function classInfo($fullClassName)
	{
		$info = explode('\\', $fullClassName);
		$list = [];
		$list['className'] = array_pop($info);
		if (!empty($info)) {
			$list['namespace'] = '';
			foreach ($info as $path) {
				if ($list['namespace'] != '') {
					$list['namespace'] .= '\\';
				}
				$list['namespace'] .= $path;
			}
		}
		return $list;
	}
	
	protected static function nsJoin($nsLeft, $nsRight)
	{
		$ns = '';
		$info = array_merge(explode('\\', $nsLeft), explode('\\', $nsRight));
		foreach ($info as $path) {
			if (!$path) {
				continue;
			}
			if ($ns != '') {
				$ns .= '\\';
			}
			$ns .= $path;
		}
		return $ns;
	}
	
	protected static function nsToPath($rootPath, $ns)
	{
		$info = explode('\\', $ns);
		$rightPath = '';
		foreach ($info as $path) {
			if (!$path) {
				continue;
			}
			if ($rightPath != '') {
				$rightPath .= DIRECTORY_SEPARATOR;
			}
			$rightPath .= $path;
		}
		if ($rightPath) {
			$rootPath .= DIRECTORY_SEPARATOR . $rightPath;
		}
		return $rootPath;
	}
}