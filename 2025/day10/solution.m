fid = fopen("input", 'r');

total_presses = 0;

while ~feof(fid)
    line = fgetl(fid);
    if ~ischar(line)
        break;
    end
    
    joltage = regexp(line, '\{([^}]+)\}', 'tokens');
    targets = str2num(joltage{1}{1});
    
    buttons = regexp(line, '\(([^)]+)\)', 'tokens');
    num_buttons = length(buttons);
    num_counters = length(targets);
    
    A = zeros(num_counters, num_buttons);
    for j = 1:num_buttons
        affected = str2num(buttons{j}{1});
        for idx = affected
            A(idx+1, j) = 1;
        end
    end

    targets = targets(:);
    [m, n] = size(A);
    
    c = ones(n, 1);
    lb = zeros(n, 1);
    ub = [];
    ctype = repmat('S', m, 1);
    vartype = repmat('I', n, 1);
    sense = 1;
    
    param.msglev = 0;
    param.itlim = 100000;
    
    [x, fval, status] = glpk(c, A, targets, lb, ub, ctype, vartype, sense, param);
    
    residual = norm(A * x - targets);
    
    total_presses += sum(x);
end

fprintf('%d\n', total_presses);
assert(total_presses == 18273);
