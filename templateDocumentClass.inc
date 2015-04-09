<?php
namespace m5D02F22739AA11E4B3C6005056847E34;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('templateDocumentProviderModeConstantClass', 'constants');
class templateDocumentClass
{
	use traits\propertysClass, instanceClass;

	const BLOCK_LIST_KEYNAME = 'blockList';
	const LABEL_LIST_KEYNAME = 'labelList';
	
	private static $_staticParams = [];
	private $_instanceParams = [
		'propertys' => [
			'ownerInstance' => [
				'get' => true,
				'set' => false,
			],
			'fileName' => [
				'get' => true,
				'set' => false,
			],
			'blockName' => [
				'get' => true,
				'set' => false,
			],
			'blockUid' => [
				'get' => true,
				'set' => false,
			],
			'rawData' => [
				'get' => true,
				'set' => false,
			],
			'templateContent' => [
				'get' => true,
				'set' => false,
			],
		]
	];

    public function __construct($blockName = '', templateDocumentClass $ownerInstance = null){
		$this->propertySet('ownerInstance', $ownerInstance);
		$this->propertySet('blockName', $blockName);
		$this->propertySet('blockUid', uniqid('td', true));
    }
	
	public function __destruct()
	{
		
	}
	
	public function loadFile($file)
	{
		if (!file_exists($file)) {
			throw new \exception("指定的檔案 [{$file}] 不存在");
		}
		$this->propertySet('fileName', $file);
		return $this->loadContents(file_get_contents($file));
	}
	
	public function loadContents($rawData)
	{
		$this->propertySet('rawData', $rawData);
		return $this->analyzeContents($rawData);
	}
	
	public function pathGet()
	{
		$ownerInstance = $this->ownerInstance;
		if (!$ownerInstance) {
			return '/';
		}
		
		$path = $ownerInstance->path;
		return $path . $this->blockName . '/';
	}
	
	protected function reset()
	{
		static $excludeMaps = [
			'ownerInstance' => '',
			'blockUid' => '',
			'blockName' => '',
			'rawData' => '',
		];
		
		foreach ($this->_instanceParams['propertys'] as $propName => &$info) {
			if (!isset($excludeMaps[$propName])) {
				unset($info['value']);
			}
		}
		
		$this->propertySet('blockUid', uniqid('td', true));
		$blockList = &$this->_instanceParams[self::BLOCK_LIST_KEYNAME];
		if ($blockList) {
			foreach ($blockList as $info) {
				$info['instance']->__destruct();
				unset($info['instance']);
			}
			unset($blockList);
			unset($this->_instanceParams[self::BLOCK_LIST_KEYNAME]);
		}
		$this->_instanceParams[self::BLOCK_LIST_KEYNAME] = [];
		$this->_instanceParams[self::LABEL_LIST_KEYNAME] = [];
	}
	
	/**
	* @brief 分析內容, 建立套版模型
	* @param string $rawData 要分析的內容
	* @return boolean 成功或失敗
	* @code
    *   # aaaaa 標籤
	* 	(s:-aaaaa-:)
	* 
	*   # aaaaa 區塊
	*   <!--:aaaaa:--> <!--/:aaaaa:-->
	* @endcode
	
	* @warning 區塊名稱不可重複, 否則會造成誤判<br/>標簽名稱可以重複
	
	* @author nico chen 2015-01-15
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-15</b>    
	*      - 建立函數			
	*/
	protected function analyzeContents($rawData)
	{
		$this->reset();
		@preg_match_all('%<!--:(?P<blockName>.*):-->(?P<rawData>.*?)<!--/:(?P=blockName):-->%si', $rawData, $matchs);
		$lastCode = preg_last_error();
		if ($lastCode != PREG_NO_ERROR) {
			$pregExceptionClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('pregExceptionClass', 'exceptions');
			throw new $pregExceptionClass();
		}
		$className = get_called_class();
		$blockList = &$this->_instanceParams[self::BLOCK_LIST_KEYNAME];
		$labelList = &$this->_instanceParams[self::LABEL_LIST_KEYNAME];
		foreach ($matchs["blockName"] as $idx => $blocName){
			if (!isset($blockList[$blocName])) {
				$childInstance = new $className($blocName, $this);
				$childInstance->loadContents($matchs["rawData"][$idx]);
				$childBlockUid = $childInstance->blockUid;
				$blockList[$blocName] = [
					'blockUid' => $childBlockUid,
					'instance' => $childInstance,
				];
				$rawData = preg_replace("%<!--:{$blocName}:-->(?P<rawData>.*?)<!--/:{$blocName}:-->%si", "(t:-{$childInstance->blockUid}-:)", $rawData);
			}
		};
		$this->propertySet('templateContent', $rawData);
		if (preg_match_all('/\(s:-(?P<labelName>.*?)-:\)/si', $rawData, $matchs)){
			foreach($matchs["labelName"] as $labelName){
				$labelList[$labelName] = '';
			};
		};
		unset($blockList);
		unset($labelList);
	}
	
	public function out(\m5D02F22739AA11E4B3C6005056847E34\templateDocumentProviderInterface $templateDocumentProviderInstance)
	{
		$content = $this->templateContent;
		$blockList = &$this->_instanceParams[self::BLOCK_LIST_KEYNAME];
		$labelList = &$this->_instanceParams[self::LABEL_LIST_KEYNAME];
		$path = $this->path;
		$fileName = $this->fileName;
		if ($labelList) {
			foreach ($labelList as $labelName => $noUsed) {
				if ($templateDocumentProviderInstance instanceof templateDocumentProvider2Interface) {
					$templateDocumentProviderInstance->queryValue($this, \m5D02F22739AA11E4B3C6005056847E34\constants\templateDocumentProviderModeConstantClass::MODE_LABEL, $labelName, $value);
				} else {
					$templateDocumentProviderInstance->queryValue($this, \m5D02F22739AA11E4B3C6005056847E34\constants\templateDocumentProviderModeConstantClass::MODE_LABEL, $path . $labelName, $value);
				};
				if (is_null($value)) {
					$value = 'label=>' . $path . $labelName;
				}
				$content = preg_replace("/\(s:-{$labelName}-:\)/si", $value, $content);
			}
		}
		if ($blockList) {
			foreach ($blockList as $blockName => $blockInfo) {
				$value = null;
				if ($templateDocumentProviderInstance instanceof templateDocumentProvider2Interface) {
					$customContent = $templateDocumentProviderInstance->queryValue($blockInfo['instance'], \m5D02F22739AA11E4B3C6005056847E34\constants\templateDocumentProviderModeConstantClass::MODE_BLOCK, '', $value);
				} else {
					$customContent = $templateDocumentProviderInstance->queryValue($blockInfo['instance'], \m5D02F22739AA11E4B3C6005056847E34\constants\templateDocumentProviderModeConstantClass::MODE_BLOCK, $path . $blockName, $value);
				};
				if (!is_null($value)) {
					if (!$customContent) {
						$blockInfo['instance']->loadContents($value);
						$value = $blockInfo['instance']->out($templateDocumentProviderInstance);
					}
				}
				if (is_null($value)) {
					$data = "樣板名稱 : {$fileName}<br/>";
					$data .= "路徑名稱 : {$path}<br/>";
					$data .= "區塊名稱 : {$blockName}<br/>";
					$id = '_' . uuid();
					$value = '<a id="' . $id . '" class="registeringWarning" style="display:none; color:red" title="test!!">&#2993;</a>';
					$value .= '<a id="' . $id . '_data" style="display:none">' . $data . '</a>';
				}
				$content = preg_replace("/\(t:-{$blockInfo['blockUid']}-:\)/si", $value, $content);
			}
		}
		return $content;
	}
}