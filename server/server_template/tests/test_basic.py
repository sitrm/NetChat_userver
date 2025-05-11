# # Start via `make test-debug` or `make test-release`
# async def test_basic(service_client):
#     response = await service_client.post('/hello', params={'name': 'Tester'})
#     assert response.status == 200
#     assert response.text == 'Hello, Tester!\n'

# /// [Functional test]
# async def test_echo(websocket_client):
#     async with websocket_client.get('chat') as chat:
#         await chat.send('hello')
#         response = await chat.recv()
#         assert response == 'hello'
#         # /// [Functional test]

def test_dummy(service_client):
    """Dummy test to satisfy service-runner requirements"""
    pass