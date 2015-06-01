<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases\pdo;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('recordsetAbstractClass', 'databases');
class recordsetClass extends \m5D02F22739AA11E4B3C6005056847E34\databases\recordsetAbstractClass
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
}