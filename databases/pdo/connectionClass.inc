<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases\pdo;

\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('connectionAbstractClass', 'databases');
class connectionClass extends  \m5D02F22739AA11E4B3C6005056847E34\databases\connectionAbstractClass {
	private $_instanceParams = [];
	
	protected function doServerInstance()
	{
		$connectionInformation = $this->connectionInformation;
		$drive = 'mysql';
		$dbname = $connectionInformation['db'];
		$host = $connectionInformation['host'];
		$username = $connectionInformation['username'];
		$password = $connectionInformation['password'];
		$dsn = "{$drive}:dbname={$dbname}; host={$host}";
		$driverOptions = [
			\PDO::ATTR_ERRMODE => \PDO::ERRMODE_EXCEPTION
		];
		$serverInstance = new \PDO($dsn, $username, $password, $driverOptions);
		$serverInstance->query('SET NAMES UTF8');
		return $serverInstance;
	}

	protected function doQuery($sqlScript){
		try {
			$statementInstance = $this->serverInstance->query($sqlScript);
			if ($statementInstance instanceof \PDOStatement) {
				$recordsetClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('recordsetClass', 'databases\pdo', '5D02F22739AA11E4B3C6005056847E34');
				return new $recordsetClass($statementInstance);
			} else {
				\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('queryExceptionClass', 'databases\exceptions', '5D02F22739AA11E4B3C6005056847E34');
				throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript);
			};
		} catch (\PDOException $exceptionInstance) {
			\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('queryExceptionClass', 'databases\exceptions', '5D02F22739AA11E4B3C6005056847E34');
			throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript, $exceptionInstance);
		} catch (\exception $exceptionInstance) {
			throw $exceptionInstance;
		}
	}

	protected function doExecute($sqlScript) 
	{
		$statementInstance = $this->serverInstance->prepare($sqlScript);
		if ($statementInstance->execute()) {
			$recordsetClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('recordsetClass', 'databases\pdo', '5D02F22739AA11E4B3C6005056847E34');
			return new $recordsetClass($statementInstance);
		} else {
			\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('queryExceptionClass', 'databases\exceptions', '5D02F22739AA11E4B3C6005056847E34');
			throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript);
		};
	}

	public function encodeData($value)
	{
		return $this->serverInstance->quote($value);
	}
	
	protected function doBegin() 
	{
		return $this->serverInstance->beginTransaction();
	}

	protected function doCommit() 
	{
		return $this->serverInstance->commit();
	}

	protected function doRollback() 
	{
		return $this->serverInstance->rollBack();
	}
}