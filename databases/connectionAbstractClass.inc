<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases;
abstract class connectionAbstractClass {
	use	\m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [
		'propertys' => [
			'connectionInformation' => [
				'get' => true,
				'set' => false,
			],
		],
	];
	
	public function __construct(array $connectionInformation)
	{
		//parent::__construct();
		$this->propertySet('connectionInformation', $connectionInformation);
	}
	
	protected function serverInstanceGet()
	{
		$keyName = __FUNCTION__;
		if (!isset($this->_instanceParams[$keyName])) {
			$this->_instanceParams[$keyName] = $this->doServerInstance();
		}
		return $this->_instanceParams[$keyName];
	}
	abstract protected function doServerInstance();
	
	public function query($sqlScript)
	{
		try {
			return $this->doQuery($sqlScript);
		} catch (\m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\exceptionClass $exceptionInstance) {
			throw $exceptionInstance;
		} catch (\exception $exceptionInstance) {
			var_dump($exceptionInstance);
			xxx();
		}
	}
	abstract protected function doQuery($sqlScript);

	public function encodeData($value)
	{
		return addslashes($value);
	}
	
	public function execute($sqlScript)
	{
		try {
			return $this->doExecute($sqlScript);
		} catch (m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\exceptionClass $exceptionInstance) {
			throw $exceptionInstance;
		} catch (\PDOException $exceptionInstance) {
			$exceptionClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('executeExceptionClass', 'databases\exceptions');
			throw new $exceptionClass($sqlScript, $exceptionInstance);
		} catch (exception $exceptionInstance) {
			var_dump($exceptionInstance);
			xxx();
		}
	}
	abstract protected function doExecute($sqlScript);
	
	/**
	* @brief 交易是否進行中
	* @return boolean 
	* @author nico chen 2015-01-22
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-22</b>    
	*      - 建立函數			
	*/
	protected function transactionProcessingGet()
	{
		$keyName = static::propMethodNameToKeyName(__FUNCTION__);
		return isset($this->_instanceParams[$keyName]) ? $this->_instanceParams[$keyName] : false;
	}
	
	public function begin()
	{
		$keyName = 'transactionProcessing';
		$this->_instanceParams[$keyName] = $this->doBegin();
		return $this->_instanceParams[$keyName];
	}
	abstract protected function doBegin();

	public function commit()
	{
		$this->doCommit();
		$keyName = 'transactionProcessing';
		$this->_instanceParams[$keyName] = false;
	}
	abstract protected function doCommit();

	public function rollback()
	{
		$this->doRollback();
		$keyName = 'transactionProcessing';
		$this->_instanceParams[$keyName] = false;
	}
	abstract protected function doRollback();
	
	protected function autoCommitGet()
	{
		return $this->doGetAutoCommit();
	}
	abstract protected function doGetAutoCommit();
	
	protected function autoCommitSet($autoCommit)
	{
		$this->doSetAutoCommit($autoCommit);
	}
	abstract protected function doSetAutoCommit($autoCommit);
}