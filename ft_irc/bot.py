

import socket
import sys
import requests as r
import re

def get_recast_response(user, inp):
  headers = { 'Authorization': 'Token de54ffec9b29cd365cefc914477b4dfc' }
  msg = { 'attachment': { 'type': 'text', 'content': inp } }
  json = { 'message': msg, 'conversation_id': user }
  res = r.post('https://api.recast.ai/build/v1/dialog', headers=headers, json=json).json()
  if len(res['results']['messages']) > 0:
    return res['results']['messages'][0]['content']
  return 'Je ne sais pas comment repondre'

try:
  if len(sys.argv) < 2:
    print('Usage : {} <port>'.format(sys.argv[0]))
    sys.exit(1)
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  try:
    s.connect(('127.0.0.1', int(sys.argv[1])))
  except:
    print('Could not connect')
    sys.exit(1)
  s.recv(4096)
  s.send(b'/nick bot\r\n')
  while True:
    inp = s.recv(4096)
    inp = inp.decode('utf-8')
    if re.match('^\'.+?\' > ', inp):
      user = ''.join(inp.split('>', 1)[0].split('\'')[1:-1])
      inp = inp.split('>', 1)[1].strip().replace('\r', '').replace('\n', '')
      resp = get_recast_response(user, inp)
      s.send('/msg {} :{}\r\n'.format(user, resp).encode('utf-8'))
except:
  print('error')
