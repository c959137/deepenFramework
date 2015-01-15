<?php
/**
* @file  
* 網頁類別
*/
namespace m5D02F22739AA11E4B3C6005056847E34\constants;
class resourceTypeConstantClass {
	const RESOURCE_TYPE_CSS = 'css';
	const RESOURCE_TYPE_JS = 'js';
	private static $_staticParams = [
		'resourceTypeList' => [
			self::RESOURCE_TYPE_CSS => '',
			self::RESOURCE_TYPE_JS => '',
		]
	];
	private $_instanceParams = [];
	
	public static function resourceTypeChecker($constantName)
	{
		static::constantChecker('resourceTypeList', $constantName);
	}
	
	protected static function constantChecker($staticArrayKeyName, $constantName)
	{
		if (!isset(self::$_staticParams[$staticArrayKeyName][$constantName])) {
			$constantNotExistsExceptionClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('constantNotExistsExceptionClass', 'exceptions');
			throw new $constantNotExistsExceptionClass(__CLASS__ . '::' . $constantName);
		}
	}
}


namespace m5D02F22739AA11E4B3C6005056847E34\pages;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('pageAbstractClass', 'pages');
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('templateDocumentProviderInterface');

/**
* 網頁抽象類別
*/
abstract class webPageAbstractClass extends pageAbstractClass implements \m5D02F22739AA11E4B3C6005056847E34\templateDocumentProviderInterface
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\arrayPathClass;

	private static $_staticParams = [];
	private $_instanceParams = [
		'provider' => []
	];

	public static function applicationInstance()
	{
		return \m5D02F22739AA11E4B3C6005056847E34\application\webApplicationClass::instance();
	}
	
	protected function onCreate()
	{
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
		$this->providerRegister('/webSite', [$this, 'webSiteGet']);							// 網域
		$this->providerRegister('/pageTitle', [$this, 'pageTitleGet']);						// 頁面抬頭
		
		$this->providerRegister('/jsList', [$this, 'jsList']);						// 頁面抬頭
		$this->providerRegister('/cssList', [$this, 'cssList']);						// 頁面抬頭

		$this->onBeforeOut();
		return $this->onOut();
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
	
	function queryValue(\m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance, $path)
	{
		return $this->providerData($templateDocumentInstance, $path);
	}
	
	protected function providerRegister($path, $value)
	{
		static::valueSet($this->_instanceParams['provider'], $path, $value);
	}
	
	protected function providerData(\m5D02F22739AA11E4B3C6005056847E34\templateDocumentClass $templateDocumentInstance, $path, $defaultValue = null)
	{
		echo $path, '<br/>';
		$value = static::valueGet($this->_instanceParams['provider'], $path, null);
		if (is_array($value)) {
			$value = call_user_func_array($value, [$templateDocumentInstance]);
		} else {
			if (is_callable($value)) {
				$value = call_user_func_array($value, [$templateDocumentInstance]);
			}
		};
		return $value;
	}
	
	protected function resourceRegister($url, array $attrs = [], $resourceType = \m5D02F22739AA11E4B3C6005056847E34\constants\resourceTypeConstantClass::RESOURCE_TYPE_JS)
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
	
	protected function jsList()
	{	
		$keyName = 'resourceRegister';
		$resourceType = \m5D02F22739AA11E4B3C6005056847E34\constants\resourceTypeConstantClass::RESOURCE_TYPE_JS;
		if (!isset($this->_instanceParams[$keyName][$resourceType])) {
			return '';
		}
		$html = '';
		foreach ($this->_instanceParams[$keyName][$resourceType] as $url => $noUsed) {
			if ($html != '') {
				$html .= "\n";
			}
			$html .= "<script type='text/javascript' src='{$url}'></script>";
		}
		return $html;
	}
	protected function cssList()
	{
		$keyName = 'resourceRegister';
		$resourceType = \m5D02F22739AA11E4B3C6005056847E34\constants\resourceTypeConstantClass::RESOURCE_TYPE_CSS;
		if (!isset($this->_instanceParams[$keyName][$resourceType])) {
			return '';
		}
		$html = '';
		foreach ($this->_instanceParams[$keyName][$resourceType] as $url => $noUsed) {
			if ($html != '') {
				$html .= "\n";
			}
			$html .= "<link rel='stylesheet' type='text/css' href='{$url}'>";
		}
		return $html;
	}
	
}