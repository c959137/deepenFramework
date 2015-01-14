<?php
namespace m5D02F22739AA11E4B3C6005056847E34;

trait arrayPathClass 
{
	protected static function arrayToPath($path)
	{
		var_dump (explode('\\', $path));
		xxx();
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
			if ($rightPath != '') {
				$rightPath .= DIRECTORY_SEPARATOR;
			}
			$rightPath .= $path;
		}
		return $rootPath . DIRECTORY_SEPARATOR . $rightPath;
	}
}

abstract class moduleManagerAbstractClass 
{
	use propertysClass, arrayPathClass;
	private static $_staticParams = [];
	private $_instanceParams = [];
	
	/**
	* @brief 取得框架實體
	* @return object 
	*/
	public static function instance()
	{
		$keyName = __FUNCTION__;
		$className = get_called_class();
		if (!isset(self::$_staticParams[$keyName][$className])) {
			self::$_staticParams[$keyName][$className] = new $className();
		}
		return self::$_staticParams[$keyName][$className];
	}

	/**
	* @brief 取得模組編號
	* @return string 
	* @author nico chen 2015-01-13
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-13</b>    
	*      - 建立函數			
	*/
	public static function moduleUid()
	{
		$keyName = __FUNCTION__;
		$root = dirname(static::actualPath());
		if (!isset(self::$_staticParams[$keyName][$root])) {
			foreach ($_SERVER as $name => $value) {
				if (strpos($name, 'MODULE_') === false) {
					continue;
				}
				if ($value == $root) {
					self::$_staticParams[$keyName][$root] = substr($name, 7, 999);
				}
			}
		}
		return isset(self::$_staticParams[$keyName][$root]) ? self::$_staticParams[$keyName][$root] : null;
	}

	/**
	* @brief 載入模組內的類別
	* @param string $className 
	* @param string $middleNs 中間的命名空間 
	* @return string 完整的類別名稱
	* @code
		$className = moduleManagerClass::classLoader('aaa');
		//完整的類別名稱 : m5D02F22739AA11E4B3C6005056847E34\aaa

		$className = moduleManagerClass::classLoader('testClass', 'exceptions');
		//完整的類別名稱 : m5D02F22739AA11E4B3C6005056847E34\exceptions\testClass
		
	* @endcode
	* @author nico chen 2015-01-13
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-13</b>    
	*      - 建立函數			
	*/
	public static function classLoader($className, $middleNs = '')
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = [];
		}
		$classInfo = static::classInfo(get_called_class());
		$ns = static::nsJoin($classInfo['namespace'], $middleNs);
		$fullClassName = $ns . '\\' . $className;
		$moduleUid = static::moduleUid();
		if (class_exists($fullClassName) || trait_exists($fullClassName)) {
			self::$_staticParams[$keyName][$moduleUid][$fullClassName] = '';
			return $fullClassName;
		}
		$pathRoot = static::nsToPath(dirname(static::actualPath()), $middleNs);
		if (!isset(self::$_staticParams[$keyName][$moduleUid])) {
			$fn = $pathRoot . DIRECTORY_SEPARATOR . $className . '.inc';
			if (!file_exists($fn)) {
				throw new \exception("指定的檔案 [{$fn}] 不存在");
			}
			require $fn;
			if (!(class_exists($fullClassName) || trait_exists($fullClassName))) {
				throw new \exception("指定的類別 [{$fullClassName}] 不存在");
			}
			self::$_staticParams[$keyName][$moduleUid][$fullClassName] = [
				'file' => $fn
			];
		}
		return $fullClassName;
	}

	/**
	* @brief 取得模組實際檔案路徑
	* @return string 
	* @see actualPath
	* @author nico chen 2015-01-14
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-14</b>    
	*      - 建立函數			
	*/
	abstract protected function actualPathGet();

	/**
	* @brief 取得模組實際檔案路徑
	* @return string 
	* @see actualPathGet
	* @author nico chen 2015-01-14
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-14</b>    
	*      - 建立函數			
	*/
	public static function actualPath(){
		$instance = static::instance();
		return $instance->actualPath;
	}
	
	public static function show()
	{
		var_dump(self::$_staticParams);
	}
}

