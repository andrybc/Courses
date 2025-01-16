<?php
// Enable CORS
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');
header('Content-Type: application/json');

// Handle preflight requests
if ($_SERVER['REQUEST_METHOD'] === 'OPTIONS') {
    http_response_code(200);
    exit();
}

// Parse the incoming request
function getRequestInfo()
{
    return json_decode(file_get_contents('php://input'), true);
}

// Send JSON response
function sendResponse($status, $message, $data = null)
{
    echo json_encode([
        'status' => $status,
        'message' => $message,
        'data' => $data,
    ]);
    exit();
}

// Get input data
$inData = getRequestInfo();

// Validate input
if (!isset($inData['login']) || !isset($inData['password'])) {
    sendResponse('error', 'Missing login or password');
}

// Connect to the database
$conn = new mysqli('localhost', 'root', 'WeLoveCOP4331', 'COP4331');

// Check connection
if ($conn->connect_error) {
    sendResponse('error', 'Database connection failed: ' . $conn->connect_error);
}

// Prepare and execute SQL query
$stmt = $conn->prepare('SELECT ID, FirstName, LastName FROM Users WHERE Login = ? AND Password = ?');
$stmt->bind_param('ss', $inData['login'], $inData['password']);
$stmt->execute();
$result = $stmt->get_result();

// Check for a matching user
if ($row = $result->fetch_assoc()) {
    sendResponse('success', 'Login successful', [
        'id' => $row['ID'],
        'firstName' => $row['FirstName'],
        'lastName' => $row['LastName'],
    ]);
} else {
    sendResponse('error', 'Invalid login or password');
}

// Clean up
$stmt->close();
$conn->close();
?>
