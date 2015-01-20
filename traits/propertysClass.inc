<?php
/**
* @file  
* 框架主檔
*/

namespace m5D02F22739AA11E4B3C6005056847E34\traits;

/**
* 屬性類別
*/
trait propertysClass 
{
	/**
	* @brief 取得屬性值
	* @param string $propName 屬性名稱
	* @return string 
	* @code
	*  依下列順序取得指定的屬性值
	*    - 方法		::$propNameGet
	*    - 靜態變數 ::$_staticParams
	*    - 動態變數 ::$_instanceParams
	
	[
		'propertys' => [
			'className' => [
				'get' => '',		// 是否可讀
				'set' => '',		// 是否可寫
				'value' => ''		// 值
			]
		]
	]
	
	* @endcode
	* @author nico chen 2015-01-13
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-13</b>    
	*      - 建立函數			
	*/
	public function __get($propName)
	{
		$methodName = $propName . 'Get';
		if (method_exists($this, $methodName)) {
			return $this->$methodName();
		}
		if (isset(self::$_staticParams)) {
			if (isset(self::$_staticParams['propertys'][$propName])) {
				self::$_staticParams['propertys'][$propName] += ['get' => true, 'value' => ''];
				return (self::$_staticParams['propertys'][$propName]['get']) ? self::$_staticParams['propertys'][$propName]['value'] : null;
			}
		}
		if (isset($this->_instanceParams)) {
			if (isset($this->_instanceParams['propertys'][$propName])) {
				$this->_instanceParams['propertys'][$propName] += ['get' => true, 'value' => ''];
				return ($this->_instanceParams['propertys'][$propName]['get']) ? $this->_instanceParams['propertys'][$propName]['value'] : null;
			}
		}
		throw new \exception ("指定的屬性 [{$propName}] 不存在");
	}

	/**
	* @brief 設定屬性值
	* @param string $propName 屬性名稱
	* @param variant $value 屬性值
	* @code
	*  依下列順序取得指定的屬性值
	*    - 方法		::$propNameSet
	*    - 靜態變數 ::$_staticParams
	*    - 動態變數 ::$_instanceParams
	* @endcode
	* @author nico chen 2015-01-13
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-13</b>    
	*      - 建立函數			
	*/
	public function __set($propName, $value)
	{
		$methodName = $propName . 'Set';
		if (method_exists($this, $methodName)) {
			return $this->$methodName($value);
		}
		if (isset(self::$_staticParams)) {
			if (isset(self::$_staticParams['propertys'][$propName])) {
				self::$_staticParams['propertys'][$propName] += ['set' => true];
				if (self::$_staticParams['propertys'][$propName]['set']) {
					self::$_staticParams['propertys'][$propName]['value'] = $value;
				}
				return;
			}
		}

		if (isset($this->_instanceParams)) {
			if (isset($this->_instanceParams['propertys'][$propName])) {
				$this->_instanceParams['propertys'][$propName] += ['set' => true];
				if ($this->_instanceParams['propertys'][$propName]['set']) {
					$this->_instanceParams['propertys'][$propName]['value'] = $value;	
				}
				return;
			}
		}
		
		throw new \exception ("指定的屬性 [{$propName}] 不存在");
	}
	
	protected function propertySet($propName, $value)
	{
		if (isset(self::$_staticParams)) {
			if (isset(self::$_staticParams['propertys'][$propName])) {
				self::$_staticParams['propertys'][$propName]['value'] = $value;
				return;
			}
		}
		if (isset($this->_instanceParams)) {
			if (isset($this->_instanceParams['propertys'][$propName])) {
				$this->_instanceParams['propertys'][$propName]['value'] = $value;	
				return;
			}
		}
		throw new \exception ("指定的屬性 [{$propName}] 不存在");
	}
	
	protected static function propMethodNameToKeyName($propMethodName)
	{
		return preg_replace('/[G|S]et_?$/m', '', $propMethodName);
	}
	
	protected function propertyKeyList()
	{
		if (isset(self::$_staticParams)) {
			if (isset(self::$_staticParams['propertys'])) {
				return array_keys(self::$_staticParams['propertys']);
			}
		}
		if (isset($this->_instanceParams)) {
			if (isset($this->_instanceParams['propertys'])) {
				return array_keys($this->_instanceParams['propertys']);
			}
		}
		return null;
	}
}
