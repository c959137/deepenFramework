<?php
namespace m5D02F22739AA11E4B3C6005056847E34;

class templateDocumentClass
{
	use propertysClass, instanceClass;

	private static $_staticParams = [];
	private $_instanceParams = [
		'propertys' => [
			'ownerInstance' => [
				'get' => true,
				'set' => false,
			],
			'blockName' => [
				'get' => true,
				'set' => false,
			],
			
			'rawData' => [
				'get' => true,
				'set' => false,
			],
		]
	];

    public function __construct($blockName = '', templateDocumentClass $ownerInstance = null){
		$this->propertySet('ownerInstance', $ownerInstance);
		$this->propertySet('blockName', $blockName);
    }
	
	public function loadFile($file)
	{
		if (!file_exists($file)) {
			throw new exception("指定的檔案 [{$file}] 不存在");
		}
		return $this->loadContents(file_get_contents($file));
	}
	
	public function loadContents($rawData)
	{
		$this->propertySet('rawData', $rawData);
		return $this->analyzeContents($rawData);
	}
	protected function reset()
	{
		foreach ($this->_instanceParams['propertys'] as $propName => &$info) {
			unset($info['value']);
		}
	}
	
	protected function analyzeContents($rawData)
	{
		$this->reset();
		@preg_match_all('%<!--:(?P<block>.*):-->(?P<content>.*?)<!--/:(?P=block):-->%si', $rawData, $matchs);
		$lastCode = preg_last_error();
		if ($lastCode != PREG_NO_ERROR) {
			$pregExceptionClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('pregExceptionClass', 'exceptions');
			throw new $pregExceptionClass();
		}
		foreach ($matchs["block"] as $idx => $blocName){
var_dump($matchs);
xxx();			
			if(!isset ($this->_list_by_block_name[$block_name])){
			$item = new $this->class_name($block_name, $this);
			$item->load_content($matchs["content"][$idx]);
			$this->_list_by_ident_id[$item->name] = $item;
			$this->_list_by_block_name[$item->block_name] = $item;
			$this->_sub_doc_list[$item->block_name] = null;                                         
			//$this->_sub_doc_list[$item->block_name] = "";                                         
			$content_src = preg_replace("%<!--:{$block_name}:-->(?P<content>.*?)<!--/:{$block_name}:-->%si", "(t:-{$item->name}-:)", $content_src);
			};
		};
		
	}
}