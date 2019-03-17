import zipfile
import shutil
import os
import sys

script = "GenJson.py"
docname = "Dimensions.ods"
backup = docname+".bkp"
workdir = docname+"_work"

if os.path.exists(backup):
    os.remove(backup)
shutil.copyfile(docname, backup)

with zipfile.ZipFile(docname, "r") as doc:
    doc.extractall(workdir)

scriptname = os.path.basename(script)
work_script = os.path.join(workdir, "Scripts", "python", scriptname)
if os.path.exists(work_script):
    os.remove(work_script)
shutil.copyfile(script, work_script)

script_lines = [
    '<manifest:file-entry manifest:full-path="Scripts/python/GenJson.py" manifest:media-type=""/>',
    '<manifest:file-entry manifest:full-path="Scripts/python/" manifest:media-type="application/binary"/>',
    '<manifest:file-entry manifest:full-path="Scripts/" manifest:media-type="application/binary"/>'
]

manifest_path = os.path.join(workdir, "META-INF", "manifest.xml")
manifest = []
found_lines = list(map(lambda l: False, script_lines))
insert_pos = 1
with open(manifest_path, "r") as mf:
    for il, l in enumerate(mf):
        for i, sl in enumerate(script_lines):
            if sl in l:
                found_lines[i] = True
        if "</manifest:manifest>" in l:
            insert_pos = il
        manifest.append(l)

for i, sl in enumerate(script_lines):
    if not found_lines[i]:
        manifest.insert(insert_pos, " {}\n".format(sl))

with open(manifest_path, "w") as mf:
    for ml in manifest:
        mf.write(ml)

os.remove(docname)

with zipfile.ZipFile(docname, "w", compression=zipfile.ZIP_DEFLATED) as doc:
    for root, dirs, files in os.walk(workdir):
        for d in sorted(dirs):
            p = os.path.join(root, d)
            ap = os.path.relpath(p, workdir)
            doc.write(p, ap)
        for d in sorted(files):
            p = os.path.join(root, d)
            ap = os.path.relpath(p, workdir)
            doc.write(p, ap)

shutil.rmtree(workdir)

