<?php
namespace m5D02F22739AA11E4B3C6005056847E34\application;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('applicationAbstractClass', 'application');
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('arrayPathClass', 'traits');

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
		$_SERVER['REDIRECT_URL'] = urldecode ($info['path']);
	}
};

class webApplicationClass extends applicationAbstractClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	use \m5D02F22739AA11E4B3C6005056847E34\traits\arrayPathClass;
	private static $_staticParams = [];
	private $_instanceParams = [
		'propertys' => [
			'matchs' => [
				'get' => true,
				'set' => false,
			]
		]
	];

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
				$instance = static::instance();
				$instance->propertySet('matchs', $matchs);
				$info['instance'] = new $fullClassName();
				$matched = true;
				break;
			}
		}
		if ($matched) {
			return $info['instance']->out();
		} else {
			static::header404();
		};
	}
	
	public static function header404()
	{
		header_remove();
		header('HTTP/1.1 404 Not Found');
		die();
	}
	
    public static function host()
	{
		$protocol = 'http' . (isset($_SERVER['SSL'])? 's' : '');
		return "{$protocol}://{$_SERVER['HTTP_HOST']}";
	} 	
	
	public static function requestData()
	{
		switch ($_SERVER['REQUEST_METHOD']) {
			case 'POST' :
				return $_POST;
				break;
			
			case 'GET' :
				return $_GET;
				break;
			
			default :
				return $_REQUEST;
				break;
		}
	}
	
	public static function sessionRead($sessionKeyName, $defaultValue = null)
	{
		if (session_id() == '') {
			session_start();
		}
		return (isset($_SESSION[__CLASS__][$sessionKeyName])) ? $_SESSION[__CLASS__][$sessionKeyName] : $defaultValue;
	}

	public static function sessionWrite($sessionKeyName, $sessionValue)
	{
		if (session_id() == '') {
			session_start();
		}
		$_SESSION[__CLASS__][$sessionKeyName] = $sessionValue;
	}
	
	public static function sessionRemove($sessionKeyName = '')
	{
		if (session_id() == '') {
			session_start();
		}
		if ($sessionKeyName == '') {
			unset($_SESSION[__CLASS__]);
		} else {
			unset($_SESSION[__CLASS__][$sessionKeyName]);
		};
	}
}