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
	private static $_staticParams = [];
	private $_instanceParams = [
		'propertys' => [
		]
	];

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
			'fullClassName' => '',
		];
	}
	
	public static function execute()
	{
		$pageInfo = static::pageInfoByPath($_SERVER['REDIRECT_URL'], true);
		if ($pageInfo) {
			$instance = static::instance();
			return $pageInfo['instance']->out();
		} else {
			throw new requestHeader404ExceptionClass();
		};
	}
	
	protected static function pageInfoByPath($path, $isActivePage = false)
	{ 
		$keyName = 'route';
		$matched = false;
		static $webPageClass = 'm5D02F22739AA11E4B3C6005056847E34\pages\webPageAbstractClass';
		foreach (self::$_staticParams[$keyName] as $urlPattern => &$info) {
			if (!@preg_match($urlPattern, $path, $matchs)) {
				continue;
			}
			if (empty($info['instance'])) {
				$applicationModuleClass = static::applicationModuleClass();
				$fullClassName = $applicationModuleClass::classLoader($info['className'], $info['middleName']);
				$info['fullClassName'] = $fullClassName;
				if (!is_subclass_of($fullClassName, $webPageClass)) {
					throw new \exception('[' . $fullClassName . '] 必須繼承自 [' .  $webPageClass . ']');
				}
				if ($isActivePage) {
					self::$_staticParams['activeInfo'] = &$info;
				}
				$info['instance'] = $fullClassName::instance($matchs);
				$matched = true;
				break;
			} else {
				$matched = true;
				break;
			};
		}
		if ($matched) {
			return $info;
		} else {
			return null;
		}
	}
	
	public static function pageInstance($path)
	{
		$pageInfo = static::pageInfoByPath($path);
		if (!$pageInfo) {
			return null;
		}
		return $pageInfo['instance'];
	}
	
	public static function header404()
	{
		header_remove();
		header('HTTP/1.1 404 Not Found');
		die();
	}
	
	public static function serviceName()
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			if (preg_match('%^(?P<name>[^/]+)%m', $_SERVER['SERVER_SOFTWARE'], $matchs)) {
				self::$_staticParams[$keyName] = strtolower($matchs['name']);
			} else {
				self::$_staticParams[$keyName] = '';
			};
		}
		return self::$_staticParams[$keyName];
	}
	
    public static function host()
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			$serviceName = static::serviceName();
			$protocol = 'http';
			switch ($serviceName) {
				case 'apache' : 
					$protocol = 'http' . (isset($_SERVER['SSL'])? 's' : '');
					break;
				
				case 'nginx' : 
					$protocol = 'http' . ((isset($_SERVER['HTTPS']) && ($_SERVER['HTTPS'] == 'on'))? 's' : '');
					break;
			}
			self::$_staticParams[$keyName] = "{$protocol}://{$_SERVER['HTTP_HOST']}";
		}
		return self::$_staticParams[$keyName];
	} 	
	
	public static function siteInfo()
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			$siteInfo = [];
			//$_SERVER['HTTP_HOST'] = 'news3.tester.5915941.com';
			if (!preg_match('/(?P<domain>[^:]+)(:(?P<port>[\d]+))?/sim', $_SERVER['HTTP_HOST'], $matchs)) {
				xxx();
			}
			$serviceName = static::serviceName();
			$siteInfo['protocol'] = 'http';
			$siteInfo['domain'] = $matchs['domain'];
			switch ($serviceName) {
				case 'apache' : 
					$siteInfo['protocol'] = 'http' . (isset($_SERVER['SSL'])? 's' : '');
					break;
				
				case 'nginx' : 
					$siteInfo['protocol'] = 'http' . ((isset($_SERVER['HTTPS']) && ($_SERVER['HTTPS'] == 'on'))? 's' : '');
					break;
			}
			$siteInfo['outSidePort'] = isset($matchs['port']) ? $matchs['port'] : (($siteInfo['protocol'] == 'http') ? '80' : '443');
			$siteInfo['inSidePort'] = $_SERVER['SERVER_PORT'];
			self::$_staticParams[$keyName] = $siteInfo;
		}
		return self::$_staticParams[$keyName];
	}

    public static function url()
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = static::host() . urldecode($_SERVER['REQUEST_URI']);
		}
		return self::$_staticParams[$keyName];
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
		if (session_status() == PHP_SESSION_NONE) {
			session_start();
		}
		$data = (isset($_SESSION[__CLASS__][$sessionKeyName])) ? $_SESSION[__CLASS__][$sessionKeyName] : $defaultValue;
		session_write_close();
		return $data;
	}

	public static function sessionWrite($sessionKeyName, $sessionValue)
	{
		if (session_status() == PHP_SESSION_NONE) {
			session_start();
		}
		$_SESSION[__CLASS__][$sessionKeyName] = $sessionValue;
		session_write_close();
	}
	
	public static function sessionRemove($sessionKeyName = '')
	{
		if (session_status() == PHP_SESSION_NONE) {
			session_start();
		}
		if ($sessionKeyName == '') {
			unset($_SESSION[__CLASS__]);
		} else {
			unset($_SESSION[__CLASS__][$sessionKeyName]);
		};
		session_write_close();
	}

	public static function sessionDestroy()
	{
		if (session_status() == PHP_SESSION_NONE) {
			session_start();
		}
		session_destroy();
		session_write_close();
	}
	
	public static function isAjax()
	{
		return (isset($_SERVER['HTTP_X_REQUESTED_WITH']));
	}
	
	public static function activePageInstance()
	{
		$keyName = __FUNCTION__;
		$keyName = 'activeInfo';
		return isset(self::$_staticParams[$keyName]) ? self::$_staticParams[$keyName] : null;
	}

	public static function isActivePageInstance(\m5D02F22739AA11E4B3C6005056847E34\pages\webPageAbstractClass $webPageInstance)
	{
		$keyName = 'activeInfo';
		if (empty(self::$_staticParams[$keyName])) {
			return false;
		}
		return $webPageInstance instanceof self::$_staticParams[$keyName]['fullClassName'];
	}
	
	protected function matchsGet()
	{
		return static::matchs();
	}
	
	public static function matchs()
	{
		if (!isset(self::$_staticParams['activeInfo'])) {
			return [];
		}
		$className = self::$_staticParams['activeInfo']['fullClassName'];
		return $className::matchs();
	}
}

class requestHeader404ExceptionClass  extends \exception
{
}