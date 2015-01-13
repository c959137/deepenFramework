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
	
	protected function classInfo($fullClassName)
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
}

class moduleManagerClass 
{
	use propertysClass, instanceClass, arrayPathClass;

	private static $_staticParams = [];
	private $_instanceParams = [];
	
	/**
	* @brief 取得模組編號
	* @return string 
	* @author nico chen 2015-01-013
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-013</b>    
	*      - 建立函數			
	*/
	public static function moduleUid()
	{
		$keyName = __FUNCTION__;
		$root = dirname(__FILE__);
		if (!isset(self::$_staticParams[$keyName][$root])) {
			foreach ($_SERVER as $name => $value) {
				if (strpos($name, 'MODULE_') === false) {
					continue;
				}
				if ($value == $root) {
					self::$_staticParams[$keyName][$root] = substr($name, 8, 999);
				}
			}
		}
		return isset(self::$_staticParams[$keyName][$root]) ? self::$_staticParams[$keyName][$root] : null;
	}

		
	/**
	* @brief 載入模組內的類別
	* @param string $className 
	* @return string 
	* @code
		$className = moduleManagerClass::classLoader('aaa');
		//完整的類別名稱 : m5D02F22739AA11E4B3C6005056847E34\aaa
	* @endcode
	* @author nico chen 2015-01-013
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-013</b>    
	*      - 建立函數			
	*/
	public static function classLoader($className)
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = [];
		}

		$classInfo = self::classInfo(get_class());
		$fullClassName = $classInfo['namespace'] . '\\' . $className;
		$moduleUid = static::moduleUid();
		if (class_exists($fullClassName) || trait_exists($fullClassName)) {
			self::$_staticParams[$keyName][$moduleUid][$fullClassName] = '';
			return $fullClassName;
		}
		$pathRoot = dirname(__FILE__);
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
}
