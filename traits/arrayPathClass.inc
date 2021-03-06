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
			throw new \exception ("路徑不允許空值");
		}
		$list = explode(DIRECTORY_SEPARATOR, preg_replace('%[/]{2,}%im', DIRECTORY_SEPARATOR, $path));

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
	
	
	public static function arrayToPath()
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
			$ds = ($path[0] == '/') ? '' : DIRECTORY_SEPARATOR;
			if ($fullPath != '') $fullPath .= $ds; 
			$fullPath .= $path;
		}
		$ds = ($fullPath[0] == '/') ? '' : DIRECTORY_SEPARATOR;
		$fullPath = $ds . $fullPath;
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
	
	protected static function nsToArray($ns)
	{
		return explode('\\', $ns);
	}
	
	protected static function pathToNs($path, array $ns = [])
	{
		$root = dirname($path);
		$moduleClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::moduleClassLoaderByPath($root);
		$modulePath = dirname($moduleClass::actualPath());
		$rightPath = str_replace($modulePath, '', $root);
		$list = explode('/', $rightPath);
		$list2 = [];
		reset($list);
		while (true) {
			$name = current($list);
			if ($name === false) {
				break;
			}
			if ($name != '') {
				$list2[] = $name;
			}
			next($list);
		};
		foreach ($ns as $value) {
			$list2[] = $value;
		}
		return implode('\\', $list2);
	}
}