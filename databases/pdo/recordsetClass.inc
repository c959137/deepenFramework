<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases\pdo;
use \m5D02F22739AA11E4B3C6005056847E34\databases\recordsetAbstractClass as recordsetAbstractClass;
class recordsetClass extends recordsetAbstractClass
{
	use	\m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [
		'propertys' => [
			'statementInstance' => [
				'get' => true,
				'set' => false,
			],
			'rowData' => [
				'get' => true,
				'set' => false,
			],
			
		],
	];
	public function __construct(\PDOStatement $statementInstance)
	{
		$this->propertySet('statementInstance', $statementInstance);
		$statementInstance->setFetchMode(\PDO::FETCH_ASSOC);
		parent::__construct();
	}
	
	protected function doFetchRow()
	{
		$statementInstance = $this->statementInstance;
		$this->propertySet('rowData', $statementInstance->fetch());
		return $this->rowData;
	}
	
	protected function recordCountGet(){
		return $this->statementInstance->rowCount();
	}
	
	protected function affectedRowsGet()
	{
		return $this->statementInstance->rowCount();
	}
	
	/*
		取得下一個資料集
	**/
	public function nextRowset()
	{
		return $this->statementInstance->nextRowset();
	}
}