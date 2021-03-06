<?php
/**
* @file  
* 網頁類別
*/
namespace m5D02F22739AA11E4B3C6005056847E34\pages;

use \m5D02F22739AA11E4B3C6005056847E34\pages\pageAbstractClass as pageAbstractClass;
use \m5D02F22739AA11E4B3C6005056847E34\templateDocumentProviderInterface as templateDocumentProviderInterface;
use \m5D02F22739AA11E4B3C6005056847E34\constants\resourceTypeConstantClass as resourceTypeConstantClass;
use \m5D02F22739AA11E4B3C6005056847E34\pages\exceptions\requestNotSupportedExceptionClass as requestNotSupportedExceptionClass;
use \m5D02F22739AA11E4B3C6005056847E34\constants\requestModeConstantClass as requestModeConstantClass;
use \m5D02F22739AA11E4B3C6005056847E34\application\webApplicationClass as webApplicationClass;

/**
* 網頁抽象類別
*/
abstract class webPageAbstractClass extends pageAbstractClass implements templateDocumentProviderInterface
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	use \m5D02F22739AA11E4B3C6005056847E34\traits\arrayPathClass;
	const SESSION_KEY_GAP = '::';
	private static $_staticParams = [];
	private $_instanceParams = [
		'propertys' => [
		],
		'provider' => []
	];

	/**
	* @brief 建構式
	* @use onCreate
	* @author nico chen 2015-03-05
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-03-05</b>    
	*      - 建立函數			
	*/
	public function __construct ()
	{
		$this->onCreate();
	}

	public static function applicationInstance()
	{
		return \m5D02F22739AA11E4B3C6005056847E34\application\webApplicationClass::instance();
	}
	
	protected function applicationInstanceGet()
	{
		return static::applicationInstance();
	}
	
	final protected function onCreate()
	{
		if (webApplicationClass::isActivePageInstance($this)) {
			try {
				$this->onBeforeRequest();
				$requestData = $this->requestHandle();
				self::$_staticParams['requestData'] = $requestData;
				$applicationInstance = $this->applicationInstance;
				
				if ($requestData) {
					$this->responseOut($requestData);
				}
/*
				if ($applicationInstance::isAjax()) {
					header('Content-Type: application/json; charset=utf-8');
					echo json_encode($requestData);
					die();
				}
*/				
			} catch (\exception $exceptionInstance) {
				$this->onExceptions($exceptionInstance);			
			}
		}
	}
	
	/**
	* @brief 處理 request 動作前
	 
	  @code
	  $this->requestMethodRegister('login', [$this, 'loginRequest']);
	  @endcode
	
	* @author nico chen 2015-01-23
	* @use onCreate
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-23</b>    
	*      - 建立函數			
	*/
	protected function onBeforeRequest(){
		
	}
	
	protected function onDestroy()
	{
	}
	
	/**
	* @brief 頁面輸出
	* @return string
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	public function out()
	{	
		try {
			$this->providerRegister('/webSite', [$this, 'webSiteGet']);							// 網域
			$this->providerRegister('/pageTitle', [$this, 'pageTitleGet']);						// 頁面抬頭
			
			$this->providerRegister('/metaList', [$this, 'metaListArea']);						// meta
			$this->providerRegister('/jsList', [$this, 'jsListArea']);							// js
			$this->providerRegister('/cssList', [$this, 'cssListArea']);						// css
			$this->onBeforeOut();
			$pageContent = $this->onOut();
			echo $pageContent;
		} catch (\exception $exceptionInstance) {
			$this->onExceptions($exceptionInstance, true);			
			xxx();
		}
	}
	
	/**
	* @brief 處理 request
	* @author nico chen 2015-01-23
	* @use onCreate
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-23</b>    
	*      - 建立函數			
	*/
	final protected function requestHandle()
	{
		$applicationInstance = static::applicationInstance();
		$requestData = $this->requestDataProcessing($applicationInstance::requestData());
		if (!isset($requestData['work']) && isset($_GET['work'])) {
			$requestData['work'] = $_GET['work'];
		}

		if (empty($requestData)) {
			return ;
		}

		if (!isset($requestData['work'])) {
			return ;
		}
		$requestMethod = $this->requestMethod($requestData['work']);
		if ($requestMethod) {
			try {
				$responseData = call_user_func_array($requestMethod, [$requestData]);
				return $responseData;
			} catch (\exception $exceptionInstance) {
				$this->onExceptions($exceptionInstance);
			}
		} else {
			throw new requestNotSupportedExceptionClass($requestData['work']);
		};
	}
	
	/**
	* @brief 發生例外時的事件
	* @param \exception $exceptionInstance 例外實體
	* @param boolean $onOutThrow 是不是在執行 onOut 時發生例外
	* @author nico chen 2015-01-23
	* @use onCreate
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-23</b>    
	*      - 建立函數			
	*/
	protected function onExceptions(\exception $exceptionInstance, $onOutThrow = false)
	{	
		if (webApplicationClass::isAjax()) {
			$responseData  = [
				'exitCode' => false,
				'exceptionClass' => get_class($exceptionInstance),
				'code' => $exceptionInstance->getCode(),
				'message' => $exceptionInstance->getMessage(),
				'file' => $exceptionInstance->getFile(),
				'line' => $exceptionInstance->getLine(),
			];
			$this->responseExceptionOut($responseData);
			die();
			
			header_remove();
			@ob_end_clean();
			header('Content-Type: application/json; charset=utf-8');
			echo json_encode($responseData);
			die();
		}
	
		if ($exceptionInstance instanceof \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass) {
			showScript($exceptionInstance->sqlScript);
			echo $exceptionInstance->getMessage(), '<br/>';
		} else if ($exceptionInstance instanceof \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\executeExceptionClass) {
			showScript($exceptionInstance->sqlScript);
			echo $exceptionInstance->getMessage(), '<br/>';
		} else {
			var_dump($exceptionInstance);
		};
		echo "onOutThrow:<br/>"; 
		var_dump($onOutThrow);
		echo get_class($exceptionInstance), '<br/>';
		echo "file => {$exceptionInstance->getFile()}<br/>";
		echo "line => {$exceptionInstance->getLine()}<br/>";
		xxx();
		throw $exceptionInstance;
	}
	
	/**
	* @brief 進行 request 處理前先呼叫, 提供開發人員預先處理資料
	* @use requestHandle
	* @author nico chen 2015-01-17
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-17</b>    
	*      - 建立函數			
	*/
	protected function requestDataProcessing (array $requestData)
	{
		return $requestData;
	}
	
	protected function  requestMethodRegister($requestName, $registerMethodInfo, array $methodModeList = [])
	{
		$keyName = __FUNCTION__;
		if (!isset($this->_instanceParams[$keyName][$requestName])) {
			if (!is_callable($registerMethodInfo)) {
				$unEnforceableExceptionClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('unEnforceableExceptionClass', 'exceptions');
				throw new $unEnforceableExceptionClass($registerMethodInfo);
			}

			if (!empty($methodModeList)) {
				$methodModeList2 = $methodModeList;
				$methodModeList = [];
				foreach ($methodModeList2 as $methodMode) {
					requestModeConstantClass::resourceTypeChecker($methodMode);
					$methodModeList[$methodMode] = $methodMode;
				}
			}

			$this->_instanceParams[$keyName][$requestName] = [
				'registerMethodInfo' => $registerMethodInfo,
				'methodModeList' => $methodModeList,
			];
		}
	}
	
	protected function requestMethod($requestName)
	{
		$keyName = 'requestMethodRegister';
		if (!isset($this->_instanceParams[$keyName][$requestName])) {
			return null;
		}
		$requestInfo = $this->_instanceParams[$keyName][$requestName];
		if (isset($requestInfo['methodModeList'][requestModeConstantClass::REQUEST_MODE_AJAX])) {
			if (webApplicationClass::isAjax()) {
				return $requestInfo['registerMethodInfo'];
			}
		} else {
			if (empty($requestInfo['methodModeList']) || (isset($requestInfo['methodModeList'][$_SERVER['REQUEST_METHOD']]))) {
				return $requestInfo['registerMethodInfo'];
			}
		};
		return null;
	}
	
	/**
	* @brief 頁面輸出前呼叫, 通常進行參數初始化或註冊
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	protected function onBeforeOut(){
	}

	/**
	* @brief 頁面輸出
	* @return string
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	abstract protected function onOut();
	
	function queryValue(\m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance, $providerMode , $path, &$rawData)
	{
		return $this->providerData($templateDocumentInstance, $path, $rawData);
	}
	
	protected function providerRegister($path, $value, $customContents = false)
	{
		$keyName = static::pathToArrayKey($path);
		$this->_instanceParams['provider'][$keyName] = [
			'customContents' => $customContents, 
			'value' => $value,
		];
	}
	
	protected function providerData(\m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance, $path, &$rawData, $defaultValue = null)
	{
		$keyName = static::pathToArrayKey($path);
		if (!isset($this->_instanceParams['provider'][$keyName])) {
			$rawData = null;
			return false;
		}
		$info = $this->_instanceParams['provider'][$keyName];
		$value = $info['value'];
		//$value = static::valueGet($this->_instanceParams['provider'], $path, null);
		if (is_array($value)) {
			$rawData = call_user_func_array($value, [$templateDocumentInstance]);
		} else {
			if (is_callable($value)) {
				$rawData = call_user_func_array($value, [$templateDocumentInstance]);
			} else {
				$rawData = $value;
			}
		};
		return $info['customContents'];
	}
	
	public function resourceRegister($url, array $attrs = [], $resourceType = \m5D02F22739AA11E4B3C6005056847E34\constants\resourceTypeConstantClass::RESOURCE_TYPE_JS)
	{
		\m5D02F22739AA11E4B3C6005056847E34\constants\resourceTypeConstantClass::resourceTypeChecker($resourceType);
		$keyName = __FUNCTION__;
		if (!isset($this->_instanceParams[$keyName][$resourceType])) {
			$this->_instanceParams[$keyName][$resourceType] = [];
		}
		$this->_instanceParams[$keyName][$resourceType][$url] = $attrs;
	}
	
	/**
	* @brief 網域名稱
	* @return string
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	protected function webSiteGet()
	{
		$applicationInstance = static::applicationInstance();
		return $applicationInstance::host();
	}
	
	/**
	* @brief 頁面抬頭
	* @return string
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	protected function pageTitleGet()
	{
		return '預設頁面';
	}
	
	/**
	* @brief 匯出 meta 資料
	* @return string 
	* @author nico chen 2015-01-24
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-24</b>    
	*      - 建立函數			
	*/
	protected function metaListArea()
	{	
		return '';
	}

	/**
	* @brief 匯出 javascript 資料
	* @return string 
	* @author nico chen 2015-01-24
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-24</b>    
	*      - 建立函數			
	*/
	protected function jsListArea()
	{	
		$keyName = 'resourceRegister';
		$resourceType = \m5D02F22739AA11E4B3C6005056847E34\constants\resourceTypeConstantClass::RESOURCE_TYPE_JS;
		if (!isset($this->_instanceParams[$keyName][$resourceType])) {
			return '';
		}
		$html = '';
		foreach ($this->_instanceParams[$keyName][$resourceType] as $url => $attrs) {
			if ($html != '') {
				$html .= "\n";
			}
			$html .= static::blockContent('script', $attrs + ['type' => 'text/javascript', 'src' => $url]);
		}
		return $html;
	}

	/**
	* @brief 產生 html
	* @param string $tagName 標籤名稱
	* @param boolean $pair true: 一對標籤, false: 單標籤
	* @param mixed $attrs 屬性列表
	* @param string $content 內容
	* @return string 
	* @author nico chen 2015-03-17
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-03-17</b>    
	*      - 建立函數			
	*/
	protected static function blockContent($tagName, $attrs = [], $pair = true, $content = '') {
		$attrStr = '';
		foreach ($attrs as $name => $value) {
			if ($attrStr!= '') {
				$attrStr .= ' ';
			}
			$attrStr .= $name . '="' .  $value . '"';
		}
		$html = "<{$tagName} {$attrStr}>";
		if ($pair) {
			$html .= "{$content}</{$tagName}>";
		}
		return $html;
	}
	
	
	/**
	* @brief 匯出 css 資料
	* @return string 
	* @author nico chen 2015-01-24
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-24</b>    
	*      - 建立函數			
	*/
	protected function cssListArea()
	{
		$keyName = 'resourceRegister';
		$resourceType = \m5D02F22739AA11E4B3C6005056847E34\constants\resourceTypeConstantClass::RESOURCE_TYPE_CSS;
		if (!isset($this->_instanceParams[$keyName][$resourceType])) {
			return '';
		}
		$html = '';
		foreach ($this->_instanceParams[$keyName][$resourceType] as $url => $attrs) {
			if ($html != '') {
				$html .= "\n";
			}
			$html .= static::blockContent('link', $attrs + ['href' => $url, 'rel' => 'stylesheet', 'type' => 'text/css'], false);
		}
		return $html;
	}

	protected static function pageRootSessionKey()
	{
		$keyName = __FUNCTION__;
		$className = get_called_class();
		if (!isset(self::$_staticParams[$keyName][$className])) {
			self::$_staticParams[$keyName][$className] = 'pages';
		}
		return self::$_staticParams[$keyName][$className];
	}

	protected static function pageSessionKey()
	{
		$keyName = __FUNCTION__;
		$className = get_called_class();
		if (!isset(self::$_staticParams[$keyName][$className])) {
			self::$_staticParams[$keyName][$className] = static::pageRootSessionKey() . self::SESSION_KEY_GAP . $className;
		}
		return self::$_staticParams[$keyName][$className];
	}
	
	/**
	* @brief 顯示所有註冊的套版資料列表
	* @return string 
	* @author nico chen 2015-01-24
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-24</b>    
	*      - 建立函數			
	*/
	public static function providerShow(webPageAbstractClass $pageInstance)
	{
		var_dump($pageInstance->_instanceParams['provider']);
	}
	
	public static function instance(array $matchs = [])
	{
		$keyName = __FUNCTION__;
		$className = get_called_class();
		if (!isset(self::$_staticParams[$keyName][$className])) {
			static::matchs($matchs);
			self::$_staticParams[$keyName][$className] = new $className();
		}
		return self::$_staticParams[$keyName][$className];
	}
	
	/**
		存放 path 解析的参數
	*/
	public static function matchs($value = '')
	{
		$keyName = __FUNCTION__;
		$className = get_called_class();
		if ($value == '') {
			return isset(self::$_staticParams[$keyName][$className]) ? self::$_staticParams[$keyName][$className] : [];
		} else {
			self::$_staticParams[$keyName][$className] = $value;
		}
	}
	
	protected function matchsGet()
	{
		$keyName = static::propMethodNameToKeyName(__FUNCTION__);
		return static::$keyName();
	}
	
	protected function matchsSet($value)
	{
		$keyName = static::propMethodNameToKeyName(__FUNCTION__);
		static::$keyName($value);
	}
	
	public static function requestData() 
	{
		$keyName = __FUNCTION__;
		return isset(self::$_staticParams[$keyName]) ? self::$_staticParams[$keyName] : webApplicationClass::requestData();
	}
	
	protected function responseOut($responseData)
	{
		if (webApplicationClass::isAjax()) {
			header('Content-Type: application/json; charset=utf-8');
			echo json_encode($responseData);
			die();
		}
	}
	
	protected function responseExceptionOut($responseData)
	{
		if (webApplicationClass::isAjax()) {
			header_remove();
			@ob_end_clean();
			header('Content-Type: application/json; charset=utf-8');
			echo json_encode($responseData);
			die();
		}
	}
	
}