<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases\pdo;

\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('connectionAbstractClass', 'databases');
class connectionClass extends  \m5D02F22739AA11E4B3C6005056847E34\databases\connectionAbstractClass {
	private $_instanceParams = [];
	
	protected function doServerInstance()
	{
		$drive = 'mysql';
		$dbname = 'gameCenter';
		$host = '192.168.100.50';
		$username = 'gameCenterRoot';
		$password = 'PmoJcZc21K';
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
				return new recordsetClass($statementInstance);
			} else {
				throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript);
			};
		} catch (\PDOException $exceptionInstance) {
			throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript, $exceptionInstance);
		} catch (\exception $exceptionInstance) {
			throw $exceptionInstance;
		}
	}

	protected function doExecute($sqlScript) 
	{
		$statementInstance = $this->serverInstance->prepare($sqlScript);
		if ($statementInstance->execute()) {
			return new recordsetClass($statementInstance);
		} else {
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