<?php
namespace m5D02F22739AA11E4B3C6005056847E34\application;

/**
* @brief 應用類別
*/
abstract class applicationAbstractClass 
{
	use \m5D02F22739AA11E4B3C6005056847E34\propertysClass;
	
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
}

/**
* @brief 命令列應用類別
*/
class consoleApplicationClass extends applicationAbstractClass
{
	
}

/**
* @brief 網頁列應用類別


REQUEST_URI 包含參數

*/

/**
* 如果是 nginx 且屬於重導機制, 建立 REDIRECT_URL 
*/
if (!isset($_SERVER['REDIRECT_URL'])) {
	$info = parse_url($_SERVER['REQUEST_URI']);
	if ($_SERVER['SCRIPT_NAME'] != $info['path']) {
		$_SERVER['REDIRECT_URL'] = $info['path'];
	}
};

class webApplicationClass extends applicationAbstractClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\propertysClass;
	private static $_staticParams = [];
	private $_instanceParams = [];

	public static function applicationModuleClass()
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::moduleClassLoader(\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::applicationUid());
		}
		return self::$_staticParams[$keyName];
	}
	
	public static function route($urlPattern, $className, $middleName)
	{
		//
		@preg_match_all($urlPattern, 'test');
		$lastError = preg_last_error();
		if ($lastError != PREG_NO_ERROR) {
			$pregExceptionClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('pregExceptionClass', 'exceptions');
			throw new $pregExceptionClass();
		}
/*		
		$applicationModuleClass = static::applicationModuleClass();
		$fullClassName = $applicationModuleClass::classLoader($className, $middleName);
*/
		$keyName = __FUNCTION__;
		self::$_staticParams[$keyName][$urlPattern] = [
			'className' => $className,
			'middleName' => $middleName,
			'instance' => null,
		];
	}
	
	public static function execute()
	{
		$keyName = 'route';
		$matched = false;
		static $webPageClass = 'm5D02F22739AA11E4B3C6005056847E34\pages\webPageAbstractClass';
		foreach (self::$_staticParams[$keyName] as $urlPattern => &$info) {
			if (!@preg_match($urlPattern, $_SERVER['REDIRECT_URL'], $matchs)) {
				continue;
			}
			if (empty($info['instance'])) {
				$applicationModuleClass = static::applicationModuleClass();
				$fullClassName = $applicationModuleClass::classLoader($info['className'], $info['middleName']);
				if (!is_subclass_of($fullClassName, $webPageClass)) {
					throw new \exception('[' . $fullClassName . '] 必須繼承自 [' .  $webPageClass . ']');
				}
				$info['instance'] = new $fullClassName();
				$matched = true;
				break;
			}
		}
		if ($matched) {
			$instance = static::instance();
			$instance->_instanceParams['propertys']['matchs'] = $matchs;
			return $info['instance']->out();
		}
	}
	
    public static function host()
	{
		$protocol = 'http' . (isset($_SERVER['SSL'])? 's' : '');
		return "{$protocol}://{$_SERVER['HTTP_HOST']}";
	} 	
}