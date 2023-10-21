const fs = require('fs');
const os = require('os');
const src_path = process.argv[2];
const whole_text = fs.readFileSync(src_path, 'utf8');
const all_lines = whole_text.split('\n');

let control_json = "";
let state = 0;
let line_number = 0;
for (; line_number < all_lines.length && state < 3; line_number++) {
    const line_text = all_lines[line_number];
    if (state == 0 && line_text == '# Control') {
        state = 1;
    } else if (state == 1 && line_text == '```') {
        state = 2;
    } else if (state == 2) {
        if (line_text == '```') {
            state = 3;
        } else {
            control_json += line_text;
        }
    }
}
const control_obj = JSON.parse(control_json);
console.log(control_obj);

let head = "";
state = 0;
for (; line_number < all_lines.length && state < 4; line_number++) {
    const line_text = all_lines[line_number];
    if (state == 0 && line_text == '# Head') {
        state = 1;
    } else if (state == 1 && line_text == '```') {
        state = 2;
    } else if (state == 2) {
        if (line_text == '```') {
            state = 3;
        } else {
            head += line_text + os.EOL;
        }
    } else if (state == 3) {
        if (line_text == '# Generic') {
            state = 4; // exit for loop
        } else if (line_text == '```') {
            state = 2; // waiting for closing code segment; i.e. "```".
        }
    }
}

fs.writeFileSync(control_obj.out, head, 'utf8');
line_number--;
let generic = "";
state = 0;
for (; line_number < all_lines.length && state < 4; line_number++) {
    const line_text = all_lines[line_number];
    if (state == 0 && line_text == '# Generic') {
        state = 1;
    } else if (state == 1 && line_text == '```') {
        state = 2;
    } else if (state == 2) {
        if (line_text == '```') {
            state = 3;
        } else {
            generic += line_text + os.EOL;
        }
    } else if (state == 3) {
        if (line_text == '# Foot') {
            state = 4;
        } else if (line_text == '```') {
            state = 2;
        }
    }
}

let itype = (control_obj.itype == undefined) ? "i32" : control_obj.itype;
let stype = (control_obj.stype == undefined) ? "u32" : control_obj.stype;
for (let vtype_index = 0; vtype_index < control_obj.vtypes.length; vtype_index++) {
    console.log(vtype_index);
    let regex0 = new RegExp('<RTYPE>', 'g');
    let regex1 = new RegExp('<VTYPE>', 'g');
    let regex2 = new RegExp('<ITYPE>', 'g');
    let regex3 = new RegExp('<STYPE>', 'g');
    let special_typed = (((control_obj.rtypes != undefined) && (control_obj.rtypes.length == control_obj.vtypes.length)) ?
        generic.replace(regex0, control_obj.rtypes[vtype_index]) : generic)
            .replace(regex1, control_obj.vtypes[vtype_index])
            .replace(regex2, itype).replace(regex3, stype);
    fs.appendFileSync(control_obj.out, special_typed, 'utf8');
}

line_number--;
let foot = "";
state = 0;
for (; line_number < all_lines.length && state < 4; line_number++) {
    const line_text = all_lines[line_number];
    if (state == 0 && line_text == '# Foot') {
        state = 1;
    } else if (state == 1 && line_text == '```') {
        state = 2;
    } else if (state == 2) {
        if (line_text == '```') {
            state = 3;
        } else {
            foot += line_text + os.EOL;
        }
    } else if (state == 3) {
        if (line_text == '```') {
            state = 2;
        }
    }
}
fs.appendFileSync(control_obj.out, foot, 'utf8');
