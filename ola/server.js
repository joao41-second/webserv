// server.js
const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');
const mime = require('mime-types');

const app = express();
const PORT = process.env.PORT || 3000;
const UPLOAD_DIR = path.join(__dirname, 'uploads');

// garante a pasta uploads existe
if (!fs.existsSync(UPLOAD_DIR)) fs.mkdirSync(UPLOAD_DIR, { recursive: true });

// storage do multer (mantém nome original)
const storage = multer.diskStorage({
  destination: (req, file, cb) => cb(null, UPLOAD_DIR),
  filename: (req, file, cb) => {
    // evitar paths maliciosos
    const safeName = path.basename(file.originalname);
    cb(null, safeName);
  }
});
const upload = multer({ storage });

// serve ficheiros estáticos do frontend
app.use(express.static(path.join(__dirname, 'public')));

// helper para sanitizar nome recebido nas rotas
function safeFilename(name) {
  if (!name) return null;
  return path.basename(name);
}

// LISTAR ficheiros (GET /files)
app.get('/files', (req, res) => {
  fs.readdir(UPLOAD_DIR, (err, files) => {
    if (err) return res.status(500).json({ error: 'Erro a ler diretório' });
    // devolve nome + size + mtime
    const info = files.map(f => {
      const stat = fs.statSync(path.join(UPLOAD_DIR, f));
      return { name: f, size: stat.size, mtime: stat.mtime };
    });
    res.json(info);
  });
});

// DOWNLOAD ficheiro (GET /files/:filename)
app.get('/files/:filename', (req, res) => {
  const filename = safeFilename(req.params.filename);
  if (!filename) return res.status(400).send('Nome inválido');

  const filePath = path.join(UPLOAD_DIR, filename);
  if (!fs.existsSync(filePath)) return res.status(404).send('Ficheiro não encontrado');

  // definer header para forçar download
  res.setHeader('Content-Type', mime.lookup(filename) || 'application/octet-stream');
  res.setHeader('Content-Disposition', `attachment; filename="${encodeURIComponent(filename)}"`);
  res.sendFile(filePath);
});

// UPLOAD novo ficheiro (POST /files) — campo 'file'
app.post('/files', upload.single('file'), (req, res) => {
  if (!req.file) return res.status(400).json({ error: 'Nenhum ficheiro enviado' });
  res.json({ message: 'Ficheiro enviado', file: { name: req.file.filename, size: req.file.size } });
});

// REPLACE / PUSH (PUT /files/:filename) — substitui o ficheiro com o nome indicado
// usa multer.single('file') mesmo para PUT
app.put('/files/:filename', upload.single('file'), (req, res) => {
  const target = safeFilename(req.params.filename);
  if (!target) return res.status(400).json({ error: 'Nome inválido' });
  if (!req.file) return res.status(400).json({ error: 'Nenhum ficheiro para substituir' });

  const incomingPath = path.join(UPLOAD_DIR, req.file.filename);
  const targetPath = path.join(UPLOAD_DIR, target);

  // Se o uploaded veio com nome diferente, renomeamos para o target (substituir)
  try {
    // remove o target antigo (se existir) e move o novo para o target
    if (fs.existsSync(targetPath)) fs.unlinkSync(targetPath);
    // se o multer já gravou com o mesmo nome do target, nada a fazer
    if (req.file.filename !== target) {
      fs.renameSync(incomingPath, targetPath);
    }
    res.json({ message: 'Ficheiro substituído', file: { name: target } });
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: 'Erro a substituir ficheiro' });
  }
});

// DELETE ficheiro (DELETE /files/:filename)
app.delete('/files/:filename', (req, res) => {
  const filename = safeFilename(req.params.filename);
  if (!filename) return res.status(400).json({ error: 'Nome inválido' });

  const filePath = path.join(UPLOAD_DIR, filename);
  if (!fs.existsSync(filePath)) return res.status(404).json({ error: 'Ficheiro não encontrado' });

  fs.unlink(filePath, (err) => {
    if (err) return res.status(500).json({ error: 'Erro a apagar ficheiro' });
    res.json({ message: 'Ficheiro apagado', file: { name: filename } });
  });
});

// fallback
app.use((req, res) => res.status(404).send('Not found'));

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});

